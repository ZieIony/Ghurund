#pragma once

#include "ResourceContext.h"

namespace Ghurund {
    const Ghurund::Type& ResourceContext::TYPE = Ghurund::Type([]() {return nullptr; }, "ResourceContext");
}