#pragma once

#include "collection/String.h"
#include "core/Status.h"

namespace Ghurund {
    Status readFile(const wchar_t * name, void *& data, size_t & size);

    Status writeFile(const wchar_t * name, void * data, size_t size);
}