#pragma once

#include "Status.h"

namespace Ghurund::Core {
    Status readFile(const wchar_t * name, void *& data, size_t & size);

    Status writeFile(const wchar_t * name, void * data, size_t size);
}