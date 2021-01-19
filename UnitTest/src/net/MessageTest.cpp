#include "pch.h"
#include "CppUnitTest.h"

#include "net/Message.h"
#include "net/ClientMessage.h"
#include "net/ServerMessage.h"

#include <CRC.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
    using namespace Ghurund::Net;
    using namespace std;

    TEST_CLASS(MessageTest) {
    public:

        TEST_METHOD(Message_size) {
            Assert::AreEqual(6ull, sizeof(Ghurund::Net::Message));
            Assert::AreEqual(7ull, sizeof(Ghurund::Net::ClientMessage));
            Assert::AreEqual(7ull, sizeof(Ghurund::Net::ServerMessage));
        }

        TEST_METHOD(Message_crc) {
            Message* message = ghnew ClientConnectMessage();
            uint32_t messageSize = sizeof(ClientConnectMessage);
            message->crc = CRC::Calculate((uint8_t*)message + sizeof(message->crc), messageSize - sizeof(message->crc), CRC::CRC_32());

            Message* message2 = ghnew ClientConnectMessage();
            uint32_t message2Size = sizeof(ClientConnectMessage);
            message2->crc = CRC::Calculate((uint8_t*)message2 + sizeof(message2->crc), message2Size - sizeof(message2->crc), CRC::CRC_32());

            Assert::AreEqual(message->crc, message2->crc);
        }
    };
}
