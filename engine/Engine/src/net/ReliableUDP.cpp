#include "ReliableUDP.h"

#include "core/logging/Logger.h"

namespace Ghurund::Net {
    void ReliableUDP::confirmMessage(Connection& connection, Message& message) {
        Message* confirmation = ghnew ConfirmationMessage(message.id, message.crc);
        confirmation->calculateCrc(sizeof(ConfirmationMessage));
        socket.send(connection.Socket, confirmation, sizeof(ConfirmationMessage));
        Logger::log(LogType::INFO, _T("confirmed message id:{}, crc:{}, size:{}\n"), message.id, confirmation->crc, sizeof(ConfirmationMessage));
        delete confirmation;
    }
    
    void ReliableUDP::processUpdateMessage(Connection& connection, uint8_t* messageData) {
        Message* message = (Message*)messageData;
        int16_t messageId = message->id;
        if (abs(messageId - connection.UpdateId) < 128 && messageId <= connection.UpdateId
            || abs(messageId - connection.UpdateId) >= 128 && messageId > connection.UpdateId)
            return;

        connection.UpdateId = (uint8_t)messageId;
        onUpdateMessage(connection, *message);
    }
    
    bool ReliableUDP::isReceivedDuplicate(Connection& connection, uint8_t* messageData) {
        Message* message = (Message*)messageData;
        for (MessageItem* messageItem : connection.MessagesReceived) {
            if (messageItem->Message == *message) {
                Logger::log(LogType::INFO, _T("received duplicate message:{}\n"), message->toString());
                return true;
            }
        }
        return false;
    }
    
    Status ReliableUDP::processReliableMessage(Connection& connection, uint8_t* messageData, size_t messageSize) {
        Message* message = (Message*)messageData;
        int16_t messageId = message->id;
        if (isReceivedDuplicate(connection, messageData)) {
            confirmMessage(connection, *message);
            return Status::OK;
        }
        size_t i = 0;
        for (; i < connection.MessagesReceived.Size; i++) {
            int16_t receivedId = connection.MessagesReceived[i]->Message.id;
            if (messageId + 127 < receivedId || messageId > receivedId)
                break;
        }
        connection.MessagesReceived.insert(i, ghnew MessageItem(messageData, messageSize));
        confirmMessage(connection, *message);
        while (true) {
            if (!connection.MessagesReceived.Empty && connection.ReliableId == connection.MessagesReceived[0]->Message.id) {
                MessageItem* messageItem = connection.MessagesReceived[0];
                connection.MessagesReceived.removeAt(0);
                connection.ReliableId++;
                if (messageItem->Message.type == MessageType::RELIABLE.Value) {
                    Status result;
                    result = onReliableMessage(connection, messageItem->Message);
                    if (result != Status::OK)
                        return result;
                }
                delete messageItem;
            } else {
                if (!connection.MessagesReceived.Empty)
                    Logger::log(LogType::INFO, _T("can't pass received message connection.id:{}, message.id:{}\n"), connection.ReliableId, connection.MessagesReceived[0]->Message.id);
                break;
            }
        }
        return Status::OK;
    }
    
    void ReliableUDP::processConfirmMessage(Connection& connection, uint8_t* messageData, uint64_t time) {
        ConfirmationMessage* confirmation = (ConfirmationMessage*)messageData;
        for (size_t i = 0; i < connection.MessagesSent.Size; i++) {
            MessageItem* messageItem = connection.MessagesSent[i];
            Message& message = messageItem->Message;
            if (confirmation->confirmedCrc == message.crc && confirmation->id == message.id) {
                uint64_t rtt = time - messageItem->time;
                Logger::log(LogType::INFO, _T("got confirmation for message:{}, rtt:{}\n"), message.toString(), rtt);
                connection.Rtt = rtt;
                connection.MessagesSent.removeAt(i);
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
                Logger::log(LogType::INFO, _T("got refresh message rtt:{}\n"), rtt);
                connection.Rtt = rtt;
                connection.MessagesSent.removeAt(i);
                delete messageItem;
                return;
            }
        }
        answerRefresh(connection);
    }
    
    Status ReliableUDP::processMessages(Connection& connection, size_t size, uint64_t time) {
        Status result;
        buffer.Size = size;
        size_t consumed = 0, messageSize = 0;
        while (consumed < buffer.Size) {
            uint8_t* messageData = buffer.Data + consumed;
            Message* message = (Message*)messageData;
            if (message->type == MessageType::CONFIRM.Value) {
                messageSize = sizeof(ConfirmationMessage);
            } else if (message->type == MessageType::REFRESH.Value) {
                messageSize = sizeof(RefreshMessage);
            } else {
                result = getMessageSize(messageData, buffer.Size - consumed, messageSize);
                if (result != Status::OK)
                    return Logger::log(LogType::INFO, result, _T("invalid packet\n"));
                if (messageSize == 0)
                    return Logger::log(LogType::INFO, Status::INV_PACKET, _T("invalid packet2\n"));
            }
            if (messageSize + consumed > buffer.Size)
                return Logger::log(LogType::INFO, Status::INV_PACKET, _T("invalid packet3 msgSize:{}, buffer.Size:{}, consumed:{}\n"), messageSize, buffer.Size, consumed);
            consumed += messageSize;
            result = processMessage(connection, messageData, messageSize, time);
            if (result != Status::OK)
                return result;
        }
        return Status::OK;
    }
    
    Status ReliableUDP::processMessage(Connection& connection, uint8_t* messageData, size_t messageSize, uint64_t time) {
        Message* message = (Message*)messageData;
        Logger::log(LogType::INFO, _T("got message:{}, size:{}\n"), message->toString(), messageSize);
        if (!message->isCrcValid(messageSize))
            return Status::INV_PACKET;
        if (message->type == MessageType::UPDATE.Value) {
            processUpdateMessage(connection, messageData);
        } else if (message->type == MessageType::RELIABLE.Value || message->type == MessageType::REFRESH.Value) {
            Status result = processReliableMessage(connection, messageData, messageSize);
            if (result != Status::OK)
                return result;
        } else if (message->type == MessageType::CONFIRM.Value) {
            processConfirmMessage(connection, messageData, time);
        }
        return Status::OK;
    }
    
    Status ReliableUDP::send(Connection& connection, Message* message, size_t messageSize) {
        if (message->type == MessageType::RELIABLE.Value || message->type == MessageType::REFRESH.Value) {
            message->id = reliableId++;
        } else if (message->type == MessageType::UPDATE.Value) {
            message->id = updateId++;
        }
        message->calculateCrc(messageSize);
        Status result = socket.send(connection.Socket, message, messageSize);
        Logger::log(LogType::INFO, _T("sent message:{}, size:{}\n"), message->toString(), messageSize);
        if ((message->type == MessageType::RELIABLE.Value || message->type == MessageType::REFRESH.Value) && result == Status::OK) {
            connection.MessagesSent.add(ghnew MessageItem((uint8_t*)message, messageSize));
        }
        return result;
    }
    
    void ReliableUDP::retryMessages(Connection* connection, uint64_t time) {
        for (MessageItem* message : connection->MessagesSent) {
            if (message->retryCount == RETRY_COUNT) {
                Logger::log(LogType::INFO, _T("disconnected because number of retries was exceeded\n"));
                connections.remove(connection);
                onConnectionLost(*connection);
                delete connection;
                return;
            }
            if (message->time == 0) {
                message->time = time;
            } else if (message->time + RETRY_DELAY_MS < time) {
                socket.send(connection->Socket, message->messageData, message->messageSize);
                Message* m = (Message*)message->messageData;
                Logger::log(LogType::INFO, _T("retried message:{}\n"), m->toString());
                message->time = time;
                message->retryCount++;
            }
        }
    }
    
    Status ReliableUDP::update(uint64_t time) {
        for (Connection* connection : connections)
            retryMessages(connection, time);
        while (socket.Valid) {
            sockaddr_in socketAddr;
            size_t size;
            Status result = socket.receive(buffer.Data, buffer.Capacity, size, (sockaddr&)socketAddr);
            if (result != Status::OK)
                return result;
            if (size == 0) {
                if (connections.Size > 0 && connections[0]->MessagesReceived.Size > 0) {
                    MessageItem* messageItem = connections[0]->MessagesReceived[0];
                    Message& message = messageItem->Message;
                    Logger::log(LogType::INFO, _T("stuck message:{}\n"), messageItem->toString());
                }
                break;
            }
            Logger::log(LogType::INFO, _T("got packet size:{}\n"), size);
            Connection* connection = nullptr;
            for(Connection* c:connections){
                if (memcmp(c->Socket.AddressStruct, &socketAddr, sizeof(sockaddr)) == 0) {
                    connection = c;
                    break;
                }
            }
            if (!connection) {
                tchar address[16];
                InetNtop(AF_INET, &socketAddr.sin_addr.s_addr, (tchar*)address, 16);
                connection = onNewConnection(address, ntohs(socketAddr.sin_port));
                if (!connection)
                    return Status::CONNECTION_REJECTED;
                connections.add(connection);
            }

            connection->LastSeen = time;
            result = processMessages(*connection, size, time);
            if (result != Status::OK)
                return result;
        }
        for (Connection* connection : connections) {
            if (connection->LastSeen + REFRESH_PERIOD_MS < time && connection->MessagesSent.Empty)
                send(*connection, ghnew RefreshMessage());
        }

        return Status::OK;
    }
}