#include "List.h"

namespace Ghurund {
    template <class Value, class Key>
    const std::function<int(const void*, const void*)> List<Value, Key>::DEFAULT_COMPARISON_FUNCTION = std::function<int(const void*, const void*)>([](const void *p1, const void *p2) {
            return (*(Value*)p1 - *(Value*)p2);
    });
}