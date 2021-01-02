#pragma once

namespace Ghurund::Net {
    enum class ConnectionState {
        NOT_CONNECTED, CONNECTING, CONNECTED, DISCONNECTING
    };
}