#pragma once

#include "core/resource/ResourceFormat.h"

#include <exception>

namespace Ghurund::Core {
    class FormatNotSupportedException:public std::exception {
    public:
        const ResourceFormat& format;

        FormatNotSupportedException(const ResourceFormat& format):format(format) {}
    };
}