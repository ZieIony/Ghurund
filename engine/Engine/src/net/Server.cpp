#include "ghpch.h"
#include "Server.h"

#include "ServerMessage.h"

namespace Ghurund::Net {
	size_t Server::getMessageSize(void* data, size_t size) {
		ClientMessage* clientMessage = (ClientMessage*)data;
		ClientMessageType messageType = (ClientMessageType)clientMessage->messageType;
		if (messageType == ClientMessageType::CONNECT) {
			return sizeof(ClientConnectMessage);
		} else if (messageType == ClientMessageType::DISCONNECT) {
			return sizeof(ClientDisconnectMessage);
		}
		throw InvalidDataException();
	}

	void Server::onReliableMessage(SharedPointer<Connection>& connection, Message& message) {
		ClientMessageType messageType = (ClientMessageType)((ClientMessage&)message).messageType;
		if (messageType == ClientMessageType::CONNECT) {
			if (onNewClientConnection(*connection.get())) {
				connection->Connected = true;
				send(*connection.get(), ghnew ServerAcceptMessage(connection->Id));
			} else {
				connection->Connected = false;
				send(*connection.get(), ghnew ServerRejectMessage());
			}
			onConnected(*connection.get());
			return;
		} else if (messageType == ClientMessageType::DISCONNECT) {
			auto c = connection;
			connections.remove(connection);
			spareIds.add(connection->Id);
			onDisconnected(ClientDisconnection{ *c.get(), DisconnectionReason::CLIENT });
			return;
		}
		throw InvalidDataException();
	}

	SharedPointer<Connection> Server::onNewConnection(const String& address, uint16_t port) {
		uint16_t id = (uint16_t)connections.Size;
		if (!spareIds.Empty) {
			id = spareIds[spareIds.Size - 1];
			spareIds.removeAt(spareIds.Size - 1);
		}
		auto connection = makeShared<Connection>();
		connection->Id = id;
		connection->Socket.init(address, port);
		return connection;
	}

	Server::~Server() {
		if (hosting)
			shutdown();
	}

	void Server::host(uint16_t port) {
		socket.init((const tchar*)INADDR_ANY, port);
		socket.bind();

		hosting = true;
	}

	void Server::shutdown() {
		hosting = false;
		connections.clear();
		socket.close();
	}
}