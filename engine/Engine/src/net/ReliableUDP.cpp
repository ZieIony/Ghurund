#include "ghepch.h"
#include "ReliableUDP.h"

#include "core/logging/Logger.h"
#include <core/Exceptions.h>

namespace Ghurund::Net {
	void ReliableUDP::confirmMessage(SharedPointer<Connection>& connection, Message& message) {
		Message* confirmation = ghnew ConfirmationMessage(message.id, message.crc);
		confirmation->calculateCrc(sizeof(ConfirmationMessage));
		socket.send(connection->Socket, confirmation, sizeof(ConfirmationMessage));
		auto text = std::format(_T("confirmed message id:{}, crc:{}, size:{}\n"), message.id, confirmation->crc, sizeof(ConfirmationMessage));
		Logger::log(LogType::INFO, text.c_str());
		delete confirmation;
	}

	void ReliableUDP::processUpdateMessage(SharedPointer<Connection>& connection, uint8_t* messageData) {
		Message* message = (Message*)messageData;
		int16_t messageId = message->id;
		if (abs(messageId - connection->UpdateId) < 128 && messageId <= connection->UpdateId
			|| abs(messageId - connection->UpdateId) >= 128 && messageId > connection->UpdateId)
			return;

		connection->UpdateId = (uint8_t)messageId;
		onUpdateMessage(connection, *message);
	}

	bool ReliableUDP::isReceivedDuplicate(SharedPointer<Connection>& connection, uint8_t* messageData) {
		Message* message = (Message*)messageData;
		for (MessageItem* messageItem : connection->MessagesReceived) {
			if (messageItem->Message == *message) {
				auto text = std::format(_T("received duplicate message:{}\n"), message->toString());
				Logger::log(LogType::INFO, text.c_str());
				return true;
			}
		}
		return false;
	}

	void ReliableUDP::processReliableMessage(SharedPointer<Connection>& connection, uint8_t* messageData, size_t messageSize) {
		Message* message = (Message*)messageData;
		int16_t messageId = message->id;
		if (isReceivedDuplicate(connection, messageData)) {
			confirmMessage(connection, *message);
			return;
		}
		size_t i = 0;
		for (; i < connection->MessagesReceived.Size; i++) {
			int16_t receivedId = connection->MessagesReceived[i]->Message.id;
			if (messageId + 127 < receivedId || messageId > receivedId)
				break;
		}
		connection->MessagesReceived.insert(i, ghnew MessageItem(messageData, messageSize));
		confirmMessage(connection, *message);
		while (true) {
			if (!connection->MessagesReceived.Empty && connection->ReliableId == connection->MessagesReceived[0]->Message.id) {
				MessageItem* messageItem = connection->MessagesReceived[0];
				connection->MessagesReceived.removeAt(0);
				connection->ReliableId++;
				if (messageItem->Message.type == MessageType::RELIABLE.Value) {
					onReliableMessage(connection, messageItem->Message);
					throw InvalidDataException();
				}
				delete messageItem;
			} else {
				if (!connection->MessagesReceived.Empty) {
					auto text = std::format(_T("can't pass received message connection.id:{}, message.id:{}\n"), connection->ReliableId, connection->MessagesReceived[0]->Message.id);
					Logger::log(LogType::INFO, text.c_str());
				}
				break;
			}
		}
	}

	void ReliableUDP::processConfirmMessage(SharedPointer<Connection>& connection, uint8_t* messageData, uint64_t time) {
		ConfirmationMessage* confirmation = (ConfirmationMessage*)messageData;
		for (size_t i = 0; i < connection->MessagesSent.Size; i++) {
			MessageItem* messageItem = connection->MessagesSent[i];
			Message& message = messageItem->Message;
			if (confirmation->confirmedCrc == message.crc && confirmation->id == message.id) {
				uint64_t rtt = time - messageItem->time;
				auto text = std::format(_T("got confirmation for message:{}, rtt:{}\n"), message.toString(), rtt);
				Logger::log(LogType::INFO, text.c_str());
				connection->Rtt = rtt;
				connection->MessagesSent.removeAt(i);
				delete messageItem;
				return;
			}
		}
	}

	void ReliableUDP::answerRefresh(Connection& connection) {
		Message* message = ghnew RefreshMessage();
		message->calculateCrc(sizeof(RefreshMessage));
		socket.send(connection.Socket, message, sizeof(RefreshMessage));
		Logger::log(LogType::INFO, _T("answered refresh\n"));
		delete message;
	}

	void ReliableUDP::processRefreshMessage(Connection& connection, uint64_t time) {
		for (size_t i = 0; i < connection.MessagesSent.Size; i++) {
			MessageItem* messageItem = connection.MessagesSent[i];
			Message& message = messageItem->Message;
			if (message.type == MessageType::REFRESH.Value) {
				uint64_t rtt = time - messageItem->time;
				auto text = std::format(_T("got refresh message rtt:{}\n"), rtt);
				Logger::log(LogType::INFO, text.c_str());
				connection.Rtt = rtt;
				connection.MessagesSent.removeAt(i);
				delete messageItem;
				return;
			}
		}
		answerRefresh(connection);
	}

	void ReliableUDP::processMessages(SharedPointer<Connection>& connection, size_t size, uint64_t time) {
		size_t consumed = 0, messageSize = 0;
		while (consumed < size) {
			uint8_t* messageData = buffer.Data + consumed;
			Message* message = (Message*)messageData;
			if (message->type == MessageType::CONFIRM.Value) {
				messageSize = sizeof(ConfirmationMessage);
			} else if (message->type == MessageType::REFRESH.Value) {
				messageSize = sizeof(RefreshMessage);
			} else {
				messageSize = getMessageSize(messageData, buffer.Size - consumed);
				if (messageSize == 0) {
					Logger::log(LogType::INFO, _T("invalid packet2\n"));
					throw InvalidDataException();
				}
			}
			if (messageSize + consumed > size) {
				auto text = std::format(_T("invalid packet3 msgSize:{}, size:{}, consumed:{}\n"), messageSize, size, consumed);
				Logger::log(LogType::INFO, text.c_str());
				throw InvalidDataException();
			}
			consumed += messageSize;
			processMessage(connection, messageData, messageSize, time);
		}
	}

	void ReliableUDP::processMessage(SharedPointer<Connection>& connection, uint8_t* messageData, size_t messageSize, uint64_t time) {
		Message* message = (Message*)messageData;
		auto text = std::format(_T("got message:{}, size:{}\n"), message->toString(), messageSize);
		Logger::log(LogType::INFO, text.c_str());
		if (!message->isCrcValid(messageSize))
			throw InvalidDataException();
		if (message->type == MessageType::UPDATE.Value) {
			processUpdateMessage(connection, messageData);
		} else if (message->type == MessageType::RELIABLE.Value || message->type == MessageType::REFRESH.Value) {
			processReliableMessage(connection, messageData, messageSize);
		} else if (message->type == MessageType::CONFIRM.Value) {
			processConfirmMessage(connection, messageData, time);
		}
	}

	void ReliableUDP::send(Connection& connection, Message* message, size_t messageSize) {
		if (message->type == MessageType::RELIABLE.Value || message->type == MessageType::REFRESH.Value) {
			message->id = reliableId++;
		} else if (message->type == MessageType::UPDATE.Value) {
			message->id = updateId++;
		}
		message->calculateCrc(messageSize);
		socket.send(connection.Socket, message, messageSize);
		auto text = std::format(_T("sent message:{}, size:{}\n"), message->toString(), messageSize);
		Logger::log(LogType::INFO, text.c_str());
		if (message->type == MessageType::RELIABLE.Value || message->type == MessageType::REFRESH.Value)
			connection.MessagesSent.add(ghnew MessageItem((uint8_t*)message, messageSize));
	}

	void ReliableUDP::retryMessages(SharedPointer<Connection>& connection, uint64_t time) {
		for (MessageItem* message : connection->MessagesSent) {
			if (message->retryCount == RETRY_COUNT) {
				Logger::log(LogType::INFO, _T("disconnected because number of retries was exceeded\n"));
				SharedPointer<Connection> c = connection;
				connections.remove(connection);
				onConnectionLost(*c.get());
				return;
			}
			if (message->time == 0) {
				message->time = time;
			} else if (message->time + RETRY_DELAY_MS < time) {
				socket.send(connection->Socket, message->messageData, message->messageSize);
				Message* m = (Message*)message->messageData;
				auto text = std::format(_T("retried message:{}\n"), m->toString());
				Logger::log(LogType::INFO, text.c_str());
				message->time = time;
				message->retryCount++;
			}
		}
	}

	void ReliableUDP::update(uint64_t time) {
		for (auto& connection : connections)
			retryMessages(connection, time);
		while (socket.Valid) {
			sockaddr_in socketAddr;
			size_t size;
			socket.receive(buffer.Data, buffer.Size, size, (sockaddr&)socketAddr);
			if (size == 0) {
				if (connections.Size > 0 && connections[0]->MessagesReceived.Size > 0) {
					MessageItem* messageItem = connections[0]->MessagesReceived[0];
					Message& message = messageItem->Message;
					auto text = std::format(_T("stuck message:{}\n"), messageItem->toString());
					Logger::log(LogType::INFO, text.c_str());
				}
				break;
			}
			auto text = std::format(_T("got packet size:{}\n"), size);
			Logger::log(LogType::INFO, text.c_str());
			SharedPointer<Connection> connection;
			for (auto& c : connections) {
				if (memcmp(c->Socket.AddressStruct, &socketAddr, sizeof(sockaddr)) == 0) {
					connection = c;
					break;
				}
			}
			if (connection == nullptr) {
				tchar address[16];
				InetNtop(AF_INET, &socketAddr.sin_addr.s_addr, (tchar*)address, 16);
				connection = onNewConnection(address, ntohs(socketAddr.sin_port));
				if (connection == nullptr)
					throw InvalidStateException();
				connections.add(connection);
			}

			connection->LastSeen = time;
			processMessages(connection, size, time);
		}
		for (auto& connection : connections) {
			if (connection->LastSeen + REFRESH_PERIOD_MS < time && connection->MessagesSent.Empty)
				send(*connection.get(), ghnew RefreshMessage());
		}
	}
}