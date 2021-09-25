#pragma once

#include <core/logging/LogType.h>
#include <core/string/String.h>

namespace Ghurund::Core {
    struct Log {
        const LogType& type = LogType::INFO;
        String fileLine, message;
    };
}