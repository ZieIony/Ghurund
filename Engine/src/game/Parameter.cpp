#include "Parameter.h"
#include "ParameterManager.h"

namespace Ghurund {
    const char *Parameter::WIDTH = "Width";
    const char *Parameter::HEIGHT = "Height";

    const char *Parameter::PARTY_COLOR = "partyColor";
    const char *Parameter::RANDOM = "random";

    const char *Parameter::DIRECTION = "Direction";
    const char *Parameter::POSITION = "Position";
    const char *Parameter::ROTATION = "Rotation";
    const char *Parameter::SCALE = "Scale";
    const char *Parameter::TARGET = "Target";
    const char *Parameter::UP = "Up";
    const char *Parameter::RIGHT = "Right";
    const char *Parameter::FOV = "Fov";
    const char *Parameter::ZNEAR = "ZNear";
    const char *Parameter::ZFAR = "ZFar";

    const char *Parameter::WORLD = "World";
    const char *Parameter::VIEW = "View";
    const char *Parameter::PROJECTION = "Projection";

    void Parameter::setValue(const void * value) {
        manager->lock();
        memcpy(this->value, value, size);
        manager->unlock();
    }
}