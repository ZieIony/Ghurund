#include "ghcpch.h"
#include "Type.h"

namespace Ghurund::Core {

    template<>
    String toString(const Type& type) {
        return String(std::format(_T("{}::{}"), type.Namespace, _T("::"), type.Name).c_str());
    }
}