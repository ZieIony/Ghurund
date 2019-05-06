#include "Parameter.h"
#include "ParameterManager.h"

namespace Ghurund {
    const Ghurund::Type& Parameter::TYPE = Ghurund::Type([]() {return nullptr; }, "Parameter");
}