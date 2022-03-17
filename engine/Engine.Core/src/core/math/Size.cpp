#include "ghcpch.h"
#include "Size.h"

namespace Ghurund::Core {
    template<>
    String toString(const IntSize& obj) {
        return std::format(_T("[{}, {}]"), obj.Width, obj.Height).c_str();
    }

    template<>
    String toString(const FloatSize& obj) {
        return std::format(_T("[{}, {}]"), obj.Width, obj.Height).c_str();
    }
}