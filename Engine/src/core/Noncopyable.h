#pragma once

#include "Ghurund.h"

namespace Ghurund {
    class Noncopyable {
    public:
        Noncopyable() = default;
        Noncopyable(Noncopyable&) = delete;
        Noncopyable(const Noncopyable&) = delete;
        Noncopyable& operator=(const Noncopyable&) = delete;
    };
}