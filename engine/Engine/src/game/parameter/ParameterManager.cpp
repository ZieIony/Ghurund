#include "ghpch.h"
#include "ParameterManager.h"

#include "ValueParameter.h"
#include "TextureParameter.h"
#include "core/SharedPointer.h"
#include "graphics/texture/Textures.h"

namespace Ghurund {
    const Ghurund::Core::Type& ParameterManager::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ParameterManager>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<ParameterManager>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(ParameterManager))
            .withConstructor(CONSTRUCTOR);

        return TYPE;
    }

    ParameterManager::ParameterManager() {
        float defaultFloat = 0;
        XMFLOAT2 defaultFloat2 = {0,0};
        XMFLOAT3 defaultFloat3 = {0,0,0};
        XMMATRIX defaultMatrix = XMMatrixIdentity();

        SharedPointer<ValueParameter> viewportSize = ghnew ValueParameter(ParameterId::VIEWPORT_SIZE.ConstantName, ParameterType::FLOAT2, &defaultFloat2);
        parameters.add(viewportSize);
        XMFLOAT4 white(1, 1, 1, 1);
        SharedPointer<ValueParameter> outlineColor = ghnew ValueParameter(ParameterId::OUTLINE_COLOR.ConstantName, ParameterType::COLOR, &white);
        parameters.add(outlineColor);

        XMFLOAT4 red(1, 0, 0, 1);
        SharedPointer<ValueParameter> partyColor = ghnew ValueParameter(ParameterId::PARTY_COLOR.ConstantName, ParameterType::COLOR, &red);
        parameters.add(partyColor);
        SharedPointer<ValueParameter> random = ghnew ValueParameter(ParameterId::RANDOM.ConstantName, ParameterType::FLOAT, &defaultFloat);
        parameters.add(random);
        XMFLOAT4 gray(0.4f, 0.4f, 0.4f, 1);
        SharedPointer<ValueParameter> ambientLight = ghnew ValueParameter(ParameterId::AMBIENT_LIGHT.ConstantName, ParameterType::COLOR, &gray);
        parameters.add(ambientLight);

        SharedPointer<ValueParameter> position = ghnew ValueParameter(ParameterId::POSITION.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(position);
        SharedPointer<ValueParameter> rotation = ghnew ValueParameter(ParameterId::ROTATION.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(rotation);
        SharedPointer<ValueParameter> scale = ghnew ValueParameter(ParameterId::SCALE.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(scale);

        SharedPointer<ValueParameter> cameraDirection = ghnew ValueParameter(ParameterId::CAMERA_DIRECTION.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(cameraDirection);
        SharedPointer<ValueParameter> cameraPosition = ghnew ValueParameter(ParameterId::CAMERA_POSITION.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(cameraPosition);
        SharedPointer<ValueParameter> cameraTarget = ghnew ValueParameter(ParameterId::CAMERA_TARGET.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(cameraTarget);
        SharedPointer<ValueParameter> cameraUp = ghnew ValueParameter(ParameterId::CAMERA_UP.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(cameraUp);
        SharedPointer<ValueParameter> cameraRight = ghnew ValueParameter(ParameterId::CAMERA_RIGHT.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(cameraRight);

        SharedPointer<ValueParameter> fov = ghnew ValueParameter(ParameterId::FOV.ConstantName, ParameterType::FLOAT, &defaultFloat);
        parameters.add(fov);
        SharedPointer<ValueParameter> zNear = ghnew ValueParameter(ParameterId::ZNEAR.ConstantName, ParameterType::FLOAT, &defaultFloat);
        parameters.add(zNear);
        SharedPointer<ValueParameter> zFar = ghnew ValueParameter(ParameterId::ZFAR.ConstantName, ParameterType::FLOAT, &defaultFloat);
        parameters.add(zFar);

        SharedPointer<ValueParameter> world = ghnew ValueParameter(ParameterId::WORLD.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(world);
        SharedPointer<ValueParameter> worldIT = ghnew ValueParameter(ParameterId::WORLD_IT.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(worldIT);
        SharedPointer<ValueParameter> view = ghnew ValueParameter(ParameterId::VIEW.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(view);
        SharedPointer<ValueParameter> projection = ghnew ValueParameter(ParameterId::PROJECTION.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(projection);
        SharedPointer<ValueParameter> viewProjection = ghnew ValueParameter(ParameterId::VIEW_PROJECTION.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(viewProjection);
        SharedPointer<ValueParameter> viewProjectionInv = ghnew ValueParameter(ParameterId::VIEW_PROJECTION_INV.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(viewProjectionInv);

        SharedPointer<TextureParameter> diffuseTextureParameter = ghnew TextureParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
        parameters.add(diffuseTextureParameter);

        SharedPointer<TextureParameter> specularTextureParameter = ghnew TextureParameter(ParameterId::SPECULAR_TEXTURE.ConstantName);
        parameters.add(specularTextureParameter);

        SharedPointer<TextureParameter> normalTextureParameter = ghnew TextureParameter(ParameterId::NORMAL_TEXTURE.ConstantName);
        parameters.add(normalTextureParameter);
    }

    void ParameterManager::initDefaultTextures(ResourceManager& manager, Graphics& graphics, CommandList& commandList) {
        SharedPointer<Texture> diffuseTexture = Textures::makeDefaultDiffuse(graphics, commandList, manager);
        TextureParameter* diffuseTextureParameter = (TextureParameter*)parameters[(size_t)ParameterId::DIFFUSE_TEXTURE.Value];
        diffuseTextureParameter->Value = diffuseTexture;

        SharedPointer<Texture> specularTexture = Textures::makeDefaultSpecular(graphics, commandList, manager);
        TextureParameter* specularTextureParameter = (TextureParameter*)parameters[(size_t)ParameterId::SPECULAR_TEXTURE.Value];
        specularTextureParameter->Value = specularTexture;

        SharedPointer<Texture> normalTexture = Textures::makeDefaultNormal(graphics, commandList, manager);
        TextureParameter* normalTextureParameter = (TextureParameter*)parameters[(size_t)ParameterId::NORMAL_TEXTURE.Value];
        normalTextureParameter->Value = normalTexture;
    }
}