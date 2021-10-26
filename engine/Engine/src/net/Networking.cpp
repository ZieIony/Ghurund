#include "ghpch.h"
#include "Networking.h"

#include "core/Exceptions.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Net {

    const Ghurund::Core::Type& Networking::GET_TYPE() {

        static const auto CONSTRUCTOR = Constructor<Networking>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Networking>("Ghurund::Net", "Networking")
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void Networking::init() {
        WSADATA w;

        if (WSAStartup(0x0202, &w)) {// there was an error
            Logger::log(LogType::ERR0R, _T("there was an error with WinSock initialization\n"));
            throw CallFailedException();
        }
        if (w.wVersion != 0x0202) { // wrong WinSock version!
            WSACleanup(); // unload ws2_32.dll
            Logger::log(LogType::ERR0R, _T("wrong WinSock version\n"));
            throw CallFailedException();
        }
    }
}