#include "ghcpch.h"
#include "ResourceFormat.h"

namespace Ghurund::Core {
    const ResourceFormat ResourceFormat::AUTO = ResourceFormat(L"", ResourceFormatOptions::CAN_SAVE | ResourceFormatOptions::CAN_LOAD);
}