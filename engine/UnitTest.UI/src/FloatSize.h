#pragma once

#include "CppUnitTest.h"

#include "core/math/Size.h"

#include <format>

namespace Microsoft::VisualStudio::CppUnitTestFramework {
    template<>
    static std::wstring ToString<Ghurund::Core::FloatSize>(const Ghurund::Core::FloatSize& t) {
        return std::format(L"{{ width={}, height={} }}", t.width, t.height);
    }
}
