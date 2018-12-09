#include "Parameter.h"
#include "ParameterManager.h"

namespace Ghurund {

    const ParameterType &ParameterType::FLOAT = ParameterType(ParameterTypeValue::FLOAT, sizeof(float));
    const ParameterType &ParameterType::FLOAT2 = ParameterType(ParameterTypeValue::FLOAT2, sizeof(XMFLOAT2));
    const ParameterType &ParameterType::FLOAT3 = ParameterType(ParameterTypeValue::FLOAT3, sizeof(XMFLOAT3));
    const ParameterType &ParameterType::MATRIX = ParameterType(ParameterTypeValue::MATRIX, sizeof(XMFLOAT4X4));

    const char *Parameter::VIEWPORT_SIZE = "viewportSize";

    const char *Parameter::PARTY_COLOR = "partyColor";
    const char *Parameter::RANDOM = "random";

    const char *Parameter::DIRECTION = "direction";
    const char *Parameter::POSITION = "position";
    const char *Parameter::ROTATION = "rotation";
    const char *Parameter::SCALE = "scale";
    const char *Parameter::TARGET = "target";
    const char *Parameter::UP = "up";
    const char *Parameter::RIGHT = "right";
    const char *Parameter::FOV = "fov";
    const char *Parameter::ZNEAR = "zNear";
    const char *Parameter::ZFAR = "zFar";

    const char *Parameter::WORLD = "world";
    const char *Parameter::WORLD_IT = "worldIT";
    const char *Parameter::VIEW = "view";
    const char *Parameter::PROJECTION = "projection";
    const char *Parameter::VIEW_PROJECTION = "viewProjection";

    void Parameter::setValue(const void * value) {
        manager->lock();
        memcpy(this->value, value, type.Size);
        manager->unlock();
    }
}