#include "ParameterManager.h"
#include "ValueParameter.h"
#include "core/ScopedPointer.h"

namespace Ghurund {
    const Ghurund::Type& ParameterManager::TYPE = Ghurund::Type([]() {return ghnew ParameterManager(); }, "ParameterManager");

    ParameterManager::ParameterManager() {
        ScopedPointer<ValueParameter> viewportSize = ghnew ValueParameter("viewportSize", ParameterType::FLOAT2);
        parameters.add(viewportSize);
        XMFLOAT4 white(1, 1, 1, 1);
        ScopedPointer<ValueParameter> outlineColor = ghnew ValueParameter("outlineColor", &white, ParameterType::COLOR);
        parameters.add(outlineColor);

        XMFLOAT4 red(1, 0, 0, 1);
        ScopedPointer<ValueParameter> partyColor = ghnew ValueParameter("partyColor", &red, ParameterType::COLOR);
        parameters.add(partyColor);
        ScopedPointer<ValueParameter> random = ghnew ValueParameter("random", ParameterType::FLOAT);
        parameters.add(random);
        XMFLOAT4 gray(0.4f, 0.4f, 0.4f, 1);
        ScopedPointer<ValueParameter> ambientLight = ghnew ValueParameter("ambientLight", &gray, ParameterType::COLOR);
        parameters.add(ambientLight);

        ScopedPointer<ValueParameter> position = ghnew ValueParameter("position", ParameterType::FLOAT3);
        parameters.add(position);
        ScopedPointer<ValueParameter> rotation = ghnew ValueParameter("rotation", ParameterType::FLOAT3);
        parameters.add(rotation);
        ScopedPointer<ValueParameter> scale = ghnew ValueParameter("scale", ParameterType::FLOAT3);
        parameters.add(scale);

        ScopedPointer<ValueParameter> cameraDirection = ghnew ValueParameter("cameraDirection", ParameterType::FLOAT3);
        parameters.add(cameraDirection);
        ScopedPointer<ValueParameter> cameraPosition = ghnew ValueParameter("cameraPosition", ParameterType::FLOAT3);
        parameters.add(cameraPosition);
        ScopedPointer<ValueParameter> cameraTarget = ghnew ValueParameter("cameraTarget", ParameterType::FLOAT3);
        parameters.add(cameraTarget);
        ScopedPointer<ValueParameter> cameraUp = ghnew ValueParameter("cameraUp", ParameterType::FLOAT3);
        parameters.add(cameraUp);
        ScopedPointer<ValueParameter> cameraRight = ghnew ValueParameter("cameraRight", ParameterType::FLOAT3);
        parameters.add(cameraRight);

        ScopedPointer<ValueParameter> fov = ghnew ValueParameter("fov", ParameterType::FLOAT);
        parameters.add(fov);
        ScopedPointer<ValueParameter> zNear = ghnew ValueParameter("zNear", ParameterType::FLOAT);
        parameters.add(zNear);
        ScopedPointer<ValueParameter> zFar = ghnew ValueParameter("zFar", ParameterType::FLOAT);
        parameters.add(zFar);

        XMMATRIX identity = XMMatrixIdentity();
        ScopedPointer<ValueParameter> world = ghnew ValueParameter("world", &identity, ParameterType::MATRIX);
        parameters.add(world);
        ScopedPointer<ValueParameter> worldIT = ghnew ValueParameter("worldIT", &identity, ParameterType::MATRIX);
        parameters.add(worldIT);
        ScopedPointer<ValueParameter> view = ghnew ValueParameter("view", &identity, ParameterType::MATRIX);
        parameters.add(view);
        ScopedPointer<ValueParameter> projection = ghnew ValueParameter("projection", &identity, ParameterType::MATRIX);
        parameters.add(projection);
        ScopedPointer<ValueParameter> viewProjection = ghnew ValueParameter("viewProjection", &identity, ParameterType::MATRIX);
        parameters.add(viewProjection);
    }
}