#pragma once

#include <exception>

namespace Ghurund {
    class DirectX12NotSupportedException:public std::exception {};
}