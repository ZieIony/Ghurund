#pragma once

#include <exception>

namespace Ghurund::Core {
    class NullPointerException:public std::exception {};
}