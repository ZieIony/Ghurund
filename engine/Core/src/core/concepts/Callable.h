#pragma once

#include <type_traits>

namespace Ghurund::Core {
    template<typename F, typename R, typename... Args>
    concept Callable = std::is_invocable_r_v<R, F, Args...>;
}
