#pragma once

#include <type_traits>
#include <memory>

namespace Ghurund::Core {
    template <typename T>
    struct is_shared_ptr : std::false_type {};
    
    template <typename T>
    struct is_shared_ptr<std::shared_ptr<T>> : std::true_type {};

    template <typename T>
    concept IsSharedPtr = is_shared_ptr<T>::value;

    template <typename T>
    struct is_unique_ptr : std::false_type {};
    
    template <typename T>
    struct is_unique_ptr<std::unique_ptr<T>> : std::true_type {};

    template <typename T>
    concept IsUniquePtr = is_unique_ptr<T>::value;
}
