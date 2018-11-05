#include "List.h"

namespace Ghurund {
    template <class Value>
    const std::function<int(const void*, const void*)> List<Value>::DEFAULT_COMPARISON_FUNCTION = std::function<int(const void*, const void*)>([](const void *p1, const void *p2) {
            return (*(Value*)p1 - *(Value*)p2);
    });
}