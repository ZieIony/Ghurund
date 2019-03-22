#pragma once

#include "Adapter.h"

namespace Ghurund {
    const Ghurund::Type& DisplayMode::TYPE = Ghurund::Type([]() {return nullptr; }, "DisplayMode");
    const Ghurund::Type& AdapterOutput::TYPE = Ghurund::Type([]() {return nullptr; }, "AdapterOutput");
    const Ghurund::Type& Adapter::TYPE = Ghurund::Type([]() {return nullptr; }, "Adapter");

}