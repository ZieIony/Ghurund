#include "Parameter.h"
#include "ParameterManager.h"

namespace Ghurund {
    const char *Parameter::WINDOW_WIDTH = "windowWidth";
    const char *Parameter::WINDOW_HEIGHT = "windowHeight";
    const char *Parameter::PARTY_COLOR = "partyColor";
    const char *Parameter::RANDOM = "random";

    void Parameter::setValue(const void * value) {
        manager->lock();
        memcpy(this->value, value, size);
        manager->unlock();
    }
}