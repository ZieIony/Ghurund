#include "ghepch.h"
#include "ParameterManager.h"

#include <DirectXMath.h>

namespace Ghurund::Engine {
    const Ghurund::Core::Type& ParameterManager::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<ParameterManager>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    ParameterManager::ParameterManager() {
        float defaultFloat = 0;
        ::DirectX::XMFLOAT2 defaultFloat2 = {0,0};
        ::DirectX::XMFLOAT3 defaultFloat3 = {0,0,0};
        ::DirectX::XMMATRIX defaultMatrix = ::DirectX::XMMatrixIdentity();

        /*
        ::DirectX::XMFLOAT4 white(1, 1, 1, 1);
        auto outlineColor = IntrusivePointer<Parameter>(ghnew ValueParameter(ParameterId::OUTLINE_COLOR.ConstantName, ParameterType::COLOR, &white));
        parameters.put(ParameterId::OUTLINE_COLOR, outlineColor);

        ::DirectX::XMFLOAT4 red(1, 0, 0, 1);
        auto partyColor = IntrusivePointer<Parameter>(ghnew ValueParameter(ParameterId::PARTY_COLOR.ConstantName, ParameterType::COLOR, &red));
        parameters.put(ParameterId::PARTY_COLOR, partyColor);
        auto random = IntrusivePointer<Parameter>(ghnew ValueParameter(ParameterId::RANDOM.ConstantName, ParameterType::FLOAT, &defaultFloat));
        parameters.put(random);
        ::DirectX::XMFLOAT4 gray(0.4f, 0.4f, 0.4f, 1);
        auto ambientLight = IntrusivePointer<Parameter>(ghnew ValueParameter(ParameterId::AMBIENT_LIGHT.ConstantName, ParameterType::COLOR, &gray));
        parameters.put(ambientLight);*/
    }
}
