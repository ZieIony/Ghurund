#include "ParameterManager.h"
#include "ValueParameter.h"
#include "core/ScopedPointer.h"

namespace Ghurund {
    const Ghurund::Type& ParameterManager::TYPE = Ghurund::Type([]() {return ghnew ParameterManager(); }, "ParameterManager");

    ParameterManager::ParameterManager() {
        ScopedPointer<ValueParameter> viewportSize = ghnew ValueParameter(Parameter::VIEWPORT_SIZE, ParameterValueType::FLOAT2);
        parameters.set(Parameter::VIEWPORT_SIZE, viewportSize);

        XMFLOAT4 red(1, 0, 0, 1);
        ScopedPointer<ValueParameter> partyColor = ghnew ValueParameter(Parameter::PARTY_COLOR, &red, ParameterValueType::COLOR);
        parameters.set(Parameter::PARTY_COLOR, partyColor);
        ScopedPointer<ValueParameter> random = ghnew ValueParameter(Parameter::RANDOM, ParameterValueType::FLOAT);
        parameters.set(Parameter::RANDOM, random);
        XMFLOAT4 gray(0.4f, 0.4f, 0.4f, 1);
        ScopedPointer<ValueParameter> ambientLight = ghnew ValueParameter(Parameter::AMBIENT_LIGHT, &gray, ParameterValueType::COLOR);
        parameters.set(Parameter::AMBIENT_LIGHT, ambientLight);

        ScopedPointer<ValueParameter> position = ghnew ValueParameter(Parameter::POSITION, ParameterValueType::FLOAT3);
        parameters.set(Parameter::POSITION, position);
        ScopedPointer<ValueParameter> rotation = ghnew ValueParameter(Parameter::ROTATION, ParameterValueType::FLOAT3);
        parameters.set(Parameter::ROTATION, rotation);
        ScopedPointer<ValueParameter> scale = ghnew ValueParameter(Parameter::SCALE, ParameterValueType::FLOAT3);
        parameters.set(Parameter::SCALE, scale);

        ScopedPointer<ValueParameter> cameraDirection = ghnew ValueParameter(Parameter::CAMERA_DIRECTION, ParameterValueType::FLOAT3);
        parameters.set(Parameter::CAMERA_DIRECTION, cameraDirection);
        ScopedPointer<ValueParameter> cameraPosition = ghnew ValueParameter(Parameter::CAMERA_POSITION, ParameterValueType::FLOAT3);
        parameters.set(Parameter::CAMERA_POSITION, cameraPosition);
        ScopedPointer<ValueParameter> cameraTarget = ghnew ValueParameter(Parameter::CAMERA_TARGET, ParameterValueType::FLOAT3);
        parameters.set(Parameter::CAMERA_TARGET, cameraTarget);
        ScopedPointer<ValueParameter> cameraUp = ghnew ValueParameter(Parameter::CAMERA_UP, ParameterValueType::FLOAT3);
        parameters.set(Parameter::CAMERA_UP, cameraUp);
        ScopedPointer<ValueParameter> cameraRight = ghnew ValueParameter(Parameter::CAMERA_RIGHT, ParameterValueType::FLOAT3);
        parameters.set(Parameter::CAMERA_RIGHT, cameraRight);

        ScopedPointer<ValueParameter> fov = ghnew ValueParameter(Parameter::FOV, ParameterValueType::FLOAT);
        parameters.set(Parameter::FOV, fov);
        ScopedPointer<ValueParameter> zNear = ghnew ValueParameter(Parameter::ZNEAR, ParameterValueType::FLOAT);
        parameters.set(Parameter::ZNEAR, zNear);
        ScopedPointer<ValueParameter> zFar = ghnew ValueParameter(Parameter::ZFAR, ParameterValueType::FLOAT);
        parameters.set(Parameter::ZFAR, zFar);

        XMMATRIX identity = XMMatrixIdentity();
        ScopedPointer<ValueParameter> world = ghnew ValueParameter(Parameter::WORLD, &identity, ParameterValueType::MATRIX);
        parameters.set(Parameter::WORLD, world);
        ScopedPointer<ValueParameter> worldIT = ghnew ValueParameter(Parameter::WORLD_IT, &identity, ParameterValueType::MATRIX);
        parameters.set(Parameter::WORLD_IT, worldIT);
        ScopedPointer<ValueParameter> view = ghnew ValueParameter(Parameter::VIEW, &identity, ParameterValueType::MATRIX);
        parameters.set(Parameter::VIEW, view);
        ScopedPointer<ValueParameter> projection = ghnew ValueParameter(Parameter::PROJECTION, &identity, ParameterValueType::MATRIX);
        parameters.set(Parameter::PROJECTION, projection);
        ScopedPointer<ValueParameter> viewProjection = ghnew ValueParameter(Parameter::VIEW_PROJECTION, &identity, ParameterValueType::MATRIX);
        parameters.set(Parameter::VIEW_PROJECTION, viewProjection);
    }
}