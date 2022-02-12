#include "ghcpch.h"
#include "GenericString.h"

namespace Ghurund::Core {
    template<>
    uint32_t hashCode(const GenericString<char>& data) {
        return hashCode(data.Data, sizeof(char) * data.Length);
    }

    template<>
    uint32_t hashCode(const GenericString<wchar_t>& data) {
        return hashCode(data.Data, sizeof(wchar_t) * data.Length);
    }
}
