#include "ParameterManager.h"
#include "ValueParameter.h"
#include "TextureParameter.h"
#include "core/ScopedPointer.h"
#include "resource/ResourceContext.h"
#include "graphics/texture/Textures.h"

namespace Ghurund {
    const Ghurund::Type& ParameterManager::TYPE = Ghurund::Type([]() {return ghnew ParameterManager(); }, "ParameterManager");

    ParameterManager::ParameterManager() {
        float defaultFloat = 0;
        XMFLOAT2 defaultFloat2 = {0,0};
        XMFLOAT3 defaultFloat3 = {0,0,0};
        XMMATRIX defaultMatrix = XMMatrixIdentity();

        ScopedPointer<ValueParameter> viewportSize = ghnew ValueParameter(ParameterId::VIEWPORT_SIZE.ConstantName, ParameterType::FLOAT2, &defaultFloat2);
        parameters.add(viewportSize);
        XMFLOAT4 white(1, 1, 1, 1);
        ScopedPointer<ValueParameter> outlineColor = ghnew ValueParameter(ParameterId::OUTLINE_COLOR.ConstantName, ParameterType::COLOR, &white);
        parameters.add(outlineColor);

        XMFLOAT4 red(1, 0, 0, 1);
        ScopedPointer<ValueParameter> partyColor = ghnew ValueParameter(ParameterId::PARTY_COLOR.ConstantName, ParameterType::COLOR, &red);
        parameters.add(partyColor);
        ScopedPointer<ValueParameter> random = ghnew ValueParameter(ParameterId::RANDOM.ConstantName, ParameterType::FLOAT, &defaultFloat);
        parameters.add(random);
        XMFLOAT4 gray(0.4f, 0.4f, 0.4f, 1);
        ScopedPointer<ValueParameter> ambientLight = ghnew ValueParameter(ParameterId::AMBIENT_LIGHT.ConstantName, ParameterType::COLOR, &gray);
        parameters.add(ambientLight);

        ScopedPointer<ValueParameter> position = ghnew ValueParameter(ParameterId::POSITION.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(position);
        ScopedPointer<ValueParameter> rotation = ghnew ValueParameter(ParameterId::ROTATION.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(rotation);
        ScopedPointer<ValueParameter> scale = ghnew ValueParameter(ParameterId::SCALE.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(scale);

        ScopedPointer<ValueParameter> cameraDirection = ghnew ValueParameter(ParameterId::CAMERA_DIRECTION.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(cameraDirection);
        ScopedPointer<ValueParameter> cameraPosition = ghnew ValueParameter(ParameterId::CAMERA_POSITION.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(cameraPosition);
        ScopedPointer<ValueParameter> cameraTarget = ghnew ValueParameter(ParameterId::CAMERA_TARGET.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(cameraTarget);
        ScopedPointer<ValueParameter> cameraUp = ghnew ValueParameter(ParameterId::CAMERA_UP.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(cameraUp);
        ScopedPointer<ValueParameter> cameraRight = ghnew ValueParameter(ParameterId::CAMERA_RIGHT.ConstantName, ParameterType::FLOAT3, &defaultFloat3);
        parameters.add(cameraRight);

        ScopedPointer<ValueParameter> fov = ghnew ValueParameter(ParameterId::FOV.ConstantName, ParameterType::FLOAT, &defaultFloat);
        parameters.add(fov);
        ScopedPointer<ValueParameter> zNear = ghnew ValueParameter(ParameterId::ZNEAR.ConstantName, ParameterType::FLOAT, &defaultFloat);
        parameters.add(zNear);
        ScopedPointer<ValueParameter> zFar = ghnew ValueParameter(ParameterId::ZFAR.ConstantName, ParameterType::FLOAT, &defaultFloat);
        parameters.add(zFar);

        ScopedPointer<ValueParameter> world = ghnew ValueParameter(ParameterId::WORLD.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(world);
        ScopedPointer<ValueParameter> worldIT = ghnew ValueParameter(ParameterId::WORLD_IT.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(worldIT);
        ScopedPointer<ValueParameter> view = ghnew ValueParameter(ParameterId::VIEW.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(view);
        ScopedPointer<ValueParameter> projection = ghnew ValueParameter(ParameterId::PROJECTION.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(projection);
        ScopedPointer<ValueParameter> viewProjection = ghnew ValueParameter(ParameterId::VIEW_PROJECTION.ConstantName, ParameterType::MATRIX, &defaultMatrix);
        parameters.add(viewProjection);

        ScopedPointer<TextureParameter> diffuseTextureParameter = ghnew TextureParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
        parameters.add(diffuseTextureParameter);

        ScopedPointer<TextureParameter> specularTextureParameter = ghnew TextureParameter(ParameterId::SPECULAR_TEXTURE.ConstantName);
        parameters.add(specularTextureParameter);

        ScopedPointer<TextureParameter> normalTextureParameter = ghnew TextureParameter(ParameterId::NORMAL_TEXTURE.ConstantName);
        parameters.add(normalTextureParameter);
    }

    void ParameterManager::initDefaultTextures(ResourceContext& context) {
        ScopedPointer<Texture> diffuseTexture = Textures::makeDefaultDiffuse(context);
        TextureParameter* diffuseTextureParameter = (TextureParameter*)parameters[(size_t)ParameterId::DIFFUSE_TEXTURE.Value];
        diffuseTextureParameter->Value = diffuseTexture;

        ScopedPointer<Texture> specularTexture = Textures::makeDefaultSpecular(context);
        TextureParameter* specularTextureParameter = (TextureParameter*)parameters[(size_t)ParameterId::SPECULAR_TEXTURE.Value];
        specularTextureParameter->Value = specularTexture;

        ScopedPointer<Texture> normalTexture = Textures::makeDefaultNormal(context);
        TextureParameter* normalTextureParameter = (TextureParameter*)parameters[(size_t)ParameterId::NORMAL_TEXTURE.Value];
        normalTextureParameter->Value = normalTexture;
    }
}