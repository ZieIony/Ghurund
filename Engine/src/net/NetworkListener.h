#pragma once

namespace Ghurund::Net {
    struct NetworkListener {
        virtual ~NetworkListener() {}

        virtual void onConnected() {}
        virtual void onTimeout(time_t time) {}
        virtual void onDisconnected() {}
    };
}