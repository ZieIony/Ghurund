#include "ParameterManager.h"
#include "ValueParameter.h"

namespace Ghurund {
    const Ghurund::Type& ParameterManager::TYPE = Ghurund::Type([]() {return ghnew ParameterManager(); }, "ParameterManager");

    ParameterManager::ParameterManager() {
        parameters.set(Parameter::VIEWPORT_SIZE, ghnew ValueParameter(Parameter::VIEWPORT_SIZE, ParameterType::FLOAT2));

        XMFLOAT4 red(1,0,0,1);
        parameters.set(Parameter::PARTY_COLOR, ghnew ValueParameter(Parameter::PARTY_COLOR, &red, ParameterType::COLOR));
        parameters.set(Parameter::RANDOM, ghnew ValueParameter(Parameter::RANDOM, ParameterType::FLOAT));
        XMFLOAT4 gray(0.4f,0.4f,0.4f,1);
        parameters.set(Parameter::AMBIENT_LIGHT, ghnew ValueParameter(Parameter::AMBIENT_LIGHT, &gray, ParameterType::COLOR));

        parameters.set(Parameter::POSITION, ghnew ValueParameter(Parameter::POSITION, ParameterType::FLOAT3));
        parameters.set(Parameter::ROTATION, ghnew ValueParameter(Parameter::ROTATION, ParameterType::FLOAT3));
        parameters.set(Parameter::SCALE, ghnew ValueParameter(Parameter::SCALE, ParameterType::FLOAT3));

        parameters.set(Parameter::CAMERA_DIRECTION, ghnew ValueParameter(Parameter::CAMERA_DIRECTION, ParameterType::FLOAT3));
        parameters.set(Parameter::CAMERA_POSITION, ghnew ValueParameter(Parameter::CAMERA_POSITION, ParameterType::FLOAT3));
        parameters.set(Parameter::CAMERA_TARGET, ghnew ValueParameter(Parameter::CAMERA_TARGET, ParameterType::FLOAT3));
        parameters.set(Parameter::CAMERA_UP, ghnew ValueParameter(Parameter::CAMERA_UP, ParameterType::FLOAT3));
        parameters.set(Parameter::CAMERA_RIGHT, ghnew ValueParameter(Parameter::CAMERA_RIGHT, ParameterType::FLOAT3));

        parameters.set(Parameter::FOV, ghnew ValueParameter(Parameter::FOV, ParameterType::FLOAT));
        parameters.set(Parameter::ZNEAR, ghnew ValueParameter(Parameter::ZNEAR, ParameterType::FLOAT));
        parameters.set(Parameter::ZFAR, ghnew ValueParameter(Parameter::ZFAR, ParameterType::FLOAT));

        XMMATRIX identity = XMMatrixIdentity();
        parameters.set(Parameter::WORLD, ghnew ValueParameter(Parameter::WORLD, &identity, ParameterType::MATRIX));
        parameters.set(Parameter::WORLD_IT, ghnew ValueParameter(Parameter::WORLD_IT, &identity, ParameterType::MATRIX));
        parameters.set(Parameter::VIEW, ghnew ValueParameter(Parameter::VIEW, &identity, ParameterType::MATRIX));
        parameters.set(Parameter::PROJECTION, ghnew ValueParameter(Parameter::PROJECTION, &identity, ParameterType::MATRIX));
        parameters.set(Parameter::VIEW_PROJECTION, ghnew ValueParameter(Parameter::VIEW_PROJECTION, &identity, ParameterType::MATRIX));
    }

    ParameterManager::~ParameterManager() {
        for(size_t i = 0; i<parameters.Size; i++)
            delete parameters.getValue(i);
    }
}