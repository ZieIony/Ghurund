#include "ghepch.h"

#include "ParameterManager.h"

#include "core/IntrusivePointer.h"

#include <DirectXMath.h>

namespace Ghurund::Engine {
    const Ghurund::Core::Type& ParameterManager::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ParameterManager>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<ParameterManager>(Ghurund::Engine::NAMESPACE_NAME, GH_STRINGIFY(ParameterManager))
            .withConstructor(CONSTRUCTOR);

        return TYPE;
    }

    ParameterManager::ParameterManager() {
        float defaultFloat = 0;
        ::DirectX::XMFLOAT2 defaultFloat2 = {0,0};
        ::DirectX::XMFLOAT3 defaultFloat3 = {0,0,0};
        ::DirectX::XMMATRIX defaultMatrix = ::DirectX::XMMatrixIdentity();

        /*auto viewportSize = IntrusivePointer<Parameter>(ghnew ValueParameter(ParameterId::VIEWPORT_SIZE.ConstantName, ParameterType::FLOAT2, &defaultFloat2));
        parameters.put(ParameterId::VIEWPORT_SIZE, viewportSize);
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
        parameters.put(ambientLight);

        auto position = IntrusivePointer<Parameter>(ghnew ValueParameter(ParameterId::POSITION.ConstantName, ParameterType::FLOAT3, &defaultFloat3));
        parameters.put(position);
        auto rotation = IntrusivePointer<Parameter>(ghnew ValueParameter(ParameterId::ROTATION.ConstantName, ParameterType::FLOAT3, &defaultFloat3));
        parameters.put(rotation);
        auto scale = IntrusivePointer<Parameter>(ghnew ValueParameter(ParameterId::SCALE.ConstantName, ParameterType::FLOAT3, &defaultFloat3));
        parameters.put(scale);

        auto diffuseTextureParameter = makeIntrusive<TextureParameter>(ParameterId::DIFFUSE_TEXTURE.ConstantName);
        parameters.add(diffuseTextureParameter);

        auto specularTextureParameter = makeIntrusive<TextureParameter>(ParameterId::SPECULAR_TEXTURE.ConstantName);
        parameters.add(specularTextureParameter);

        auto normalTextureParameter = makeIntrusive<TextureParameter>(ParameterId::NORMAL_TEXTURE.ConstantName);
        parameters.add(normalTextureParameter);*/
    }

    void ParameterManager::initDefaultTextures(ITextureProvider& textureProvider) {
        IntrusivePointer<ITexture> diffuseTexture(textureProvider.makeDefaultDiffuse());
        parameterDiffuse->Value = diffuseTexture.get();

        IntrusivePointer<ITexture> specularTexture(textureProvider.makeDefaultSpecular());
        parameterSpecular->Value = specularTexture.get();

        IntrusivePointer<ITexture> normalTexture(textureProvider.makeDefaultNormal());
        parameterNormal->Value = normalTexture.get();
    }
}