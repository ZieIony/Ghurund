#include "ParameterManager.h"
#include "ValueParameter.h"
#include "core/ScopedPointer.h"

namespace Ghurund {
    const Ghurund::Type& ParameterManager::TYPE = Ghurund::Type([]() {return ghnew ParameterManager(); }, "ParameterManager");

    ParameterManager::ParameterManager() {
        ScopedPointer<ValueParameter> viewportSize = ghnew ValueParameter("viewportSize", ParameterValueType::FLOAT2);
        parameters.add(viewportSize);

        XMFLOAT4 red(1, 0, 0, 1);
        ScopedPointer<ValueParameter> partyColor = ghnew ValueParameter("partyColor", &red, ParameterValueType::COLOR);
        parameters.add(partyColor);
        ScopedPointer<ValueParameter> random = ghnew ValueParameter("random", ParameterValueType::FLOAT);
        parameters.add(random);
        XMFLOAT4 gray(0.4f, 0.4f, 0.4f, 1);
        ScopedPointer<ValueParameter> ambientLight = ghnew ValueParameter("ambientLight", &gray, ParameterValueType::COLOR);
        parameters.add(ambientLight);

        ScopedPointer<ValueParameter> position = ghnew ValueParameter("position", ParameterValueType::FLOAT3);
        parameters.add(position);
        ScopedPointer<ValueParameter> rotation = ghnew ValueParameter("rotation", ParameterValueType::FLOAT3);
        parameters.add(rotation);
        ScopedPointer<ValueParameter> scale = ghnew ValueParameter("scale", ParameterValueType::FLOAT3);
        parameters.add(scale);

        ScopedPointer<ValueParameter> cameraDirection = ghnew ValueParameter("cameraDirection", ParameterValueType::FLOAT3);
        parameters.add(cameraDirection);
        ScopedPointer<ValueParameter> cameraPosition = ghnew ValueParameter("cameraPosition", ParameterValueType::FLOAT3);
        parameters.add(cameraPosition);
        ScopedPointer<ValueParameter> cameraTarget = ghnew ValueParameter("cameraTarget", ParameterValueType::FLOAT3);
        parameters.add(cameraTarget);
        ScopedPointer<ValueParameter> cameraUp = ghnew ValueParameter("cameraUp", ParameterValueType::FLOAT3);
        parameters.add(cameraUp);
        ScopedPointer<ValueParameter> cameraRight = ghnew ValueParameter("cameraRight", ParameterValueType::FLOAT3);
        parameters.add(cameraRight);

        ScopedPointer<ValueParameter> fov = ghnew ValueParameter("fov", ParameterValueType::FLOAT);
        parameters.add(fov);
        ScopedPointer<ValueParameter> zNear = ghnew ValueParameter("zNear", ParameterValueType::FLOAT);
        parameters.add(zNear);
        ScopedPointer<ValueParameter> zFar = ghnew ValueParameter("zFar", ParameterValueType::FLOAT);
        parameters.add(zFar);

        XMMATRIX identity = XMMatrixIdentity();
        ScopedPointer<ValueParameter> world = ghnew ValueParameter("world", &identity, ParameterValueType::MATRIX);
        parameters.add(world);
        ScopedPointer<ValueParameter> worldIT = ghnew ValueParameter("worldIT", &identity, ParameterValueType::MATRIX);
        parameters.add(worldIT);
        ScopedPointer<ValueParameter> view = ghnew ValueParameter("view", &identity, ParameterValueType::MATRIX);
        parameters.add(view);
        ScopedPointer<ValueParameter> projection = ghnew ValueParameter("projection", &identity, ParameterValueType::MATRIX);
        parameters.add(projection);
        ScopedPointer<ValueParameter> viewProjection = ghnew ValueParameter("viewProjection", &identity, ParameterValueType::MATRIX);
        parameters.add(viewProjection);
    }
}