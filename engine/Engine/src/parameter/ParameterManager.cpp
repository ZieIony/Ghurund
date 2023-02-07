#include "ParameterManager.h"

#include "parameter/ValueParameter.h"
#include "parameter/TextureParameter.h"
#include "core/SharedPointer.h"
#include "graphics/Textures.h"

namespace Ghurund {
    const Ghurund::Core::Type& ParameterManager::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ParameterManager>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<ParameterManager>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(ParameterManager))
            .withConstructor(CONSTRUCTOR);

        return TYPE;
    }

    ParameterManager::ParameterManager() {
        float defaultFloat = 0;
        ::DirectX::XMFLOAT2 defaultFloat2 = {0,0};
        ::DirectX::XMFLOAT3 defaultFloat3 = {0,0,0};
        ::DirectX::XMMATRIX defaultMatrix = ::DirectX::XMMatrixIdentity();

        auto viewportSize = makeShared<ValueParameter>(ParameterId::VIEWPORT_SIZE.ConstantName, ParameterType::FLOAT2, &defaultFloat2);
        parameters.add(viewportSize.get());
        ::DirectX::XMFLOAT4 white(1, 1, 1, 1);
        auto outlineColor = makeShared<ValueParameter>(ParameterId::OUTLINE_COLOR.ConstantName, ParameterType::COLOR, &white);
        parameters.add(outlineColor.get());

        ::DirectX::XMFLOAT4 red(1, 0, 0, 1);
        auto partyColor = makeShared<ValueParameter>(ParameterId::PARTY_COLOR.ConstantName, ParameterType::COLOR, &red);
        parameters.add(partyColor.get());
        auto random = makeShared<ValueParameter>(ParameterId::RANDOM.ConstantName, ParameterType::FLOAT, &defaultFloat);
        parameters.add(random.get());
        ::DirectX::XMFLOAT4 gray(0.4f, 0.4f, 0.4f, 1);
        auto ambientLight = makeShared<ValueParameter>(ParameterId::AMBIENT_LIGHT.ConstantName, ParameterType::COLOR, &gray);
        parameters.add(ambientLight.get());

        auto position = makeShared<ValueParameter>(ParameterId::POSITION.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(position.get());
        auto rotation = makeShared<ValueParameter>(ParameterId::ROTATION.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(rotation.get());
        auto scale = makeShared<ValueParameter>(ParameterId::SCALE.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(scale.get());

        auto cameraDirection = makeShared<ValueParameter>(ParameterId::CAMERA_DIRECTION.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(cameraDirection.get());
        auto cameraPosition = makeShared<ValueParameter>(ParameterId::CAMERA_POSITION.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(cameraPosition.get());
        auto cameraTarget = makeShared<ValueParameter>(ParameterId::CAMERA_TARGET.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(cameraTarget.get());
        auto cameraUp = makeShared<ValueParameter>(ParameterId::CAMERA_UP.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(cameraUp.get());
        auto cameraRight = makeShared<ValueParameter>(ParameterId::CAMERA_RIGHT.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(cameraRight.get());

        auto fov = makeShared<ValueParameter>(ParameterId::FOV.ConstantName, ParameterType::FLOAT, &defaultFloat);
        parameters.add(fov.get());
        auto zNear = makeShared<ValueParameter>(ParameterId::ZNEAR.ConstantName, ParameterType::FLOAT, &defaultFloat);
        parameters.add(zNear.get());
        auto zFar = makeShared<ValueParameter>(ParameterId::ZFAR.ConstantName, ParameterType::FLOAT, &defaultFloat);
        parameters.add(zFar.get());

        auto world = makeShared<ValueParameter>(ParameterId::WORLD.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(world.get());
        auto worldIT = makeShared<ValueParameter>(ParameterId::WORLD_IT.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(worldIT.get());
        auto view = makeShared<ValueParameter>(ParameterId::VIEW.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(view.get());
        auto projection = makeShared<ValueParameter>(ParameterId::PROJECTION.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(projection.get());
        auto viewProjection = makeShared<ValueParameter>(ParameterId::VIEW_PROJECTION.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(viewProjection.get());
        auto viewProjectionInv = makeShared<ValueParameter>(ParameterId::VIEW_PROJECTION_INV.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(viewProjectionInv.get());

        auto diffuseTextureParameter = makeShared<TextureParameter>(ParameterId::DIFFUSE_TEXTURE.ConstantName);
        parameters.add(diffuseTextureParameter.get());

        auto specularTextureParameter = makeShared<TextureParameter>(ParameterId::SPECULAR_TEXTURE.ConstantName);
        parameters.add(specularTextureParameter.get());

        auto normalTextureParameter = makeShared<TextureParameter>(ParameterId::NORMAL_TEXTURE.ConstantName);
        parameters.add(normalTextureParameter.get());
    }

    void ParameterManager::initDefaultTextures(ResourceManager& manager, Graphics& graphics, CommandList& commandList) {
        SharedPointer<Texture> diffuseTexture(Textures::makeDefaultDiffuse(graphics, commandList, manager));
        TextureParameter* diffuseTextureParameter = (TextureParameter*)parameters[(size_t)ParameterId::DIFFUSE_TEXTURE.Value];
        diffuseTextureParameter->Value = diffuseTexture.get();

        SharedPointer<Texture> specularTexture(Textures::makeDefaultSpecular(graphics, commandList, manager));
        TextureParameter* specularTextureParameter = (TextureParameter*)parameters[(size_t)ParameterId::SPECULAR_TEXTURE.Value];
        specularTextureParameter->Value = specularTexture.get();

        SharedPointer<Texture> normalTexture(Textures::makeDefaultNormal(graphics, commandList, manager));
        TextureParameter* normalTextureParameter = (TextureParameter*)parameters[(size_t)ParameterId::NORMAL_TEXTURE.Value];
        normalTextureParameter->Value = normalTexture.get();
    }
}