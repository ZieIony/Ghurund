#pragma once

#include <stdint.h>

namespace Ghurund::Core {

    inline uint32_t hashCode(const void* data, size_t size) {
        uint32_t h = 0xAAAAAAAA;
        const uint8_t* str = (const uint8_t*)data;
        for (size_t i = 0; i < size; i++) {
            h ^= ((i & 1) == 0) ? ((h << 7) ^ str[i] * (h >> 3)) :
                (~((h << 11) + str[i] ^ (h >> 5)));
        }
        return h;
    }

    template<class Type>
    inline uint32_t hashCode(const Type& data) {
        size_t size = sizeof(Type);
        return hashCode(&data, size);
    }
}
