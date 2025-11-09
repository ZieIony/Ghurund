#include "ghedxpch.h"
#include "MaterialProvider.h"

#include "engine/parameter/TextureParameter.h"
#include "engine/directx/shader/ShaderProvider.h"

namespace Ghurund::Engine::DirectX {
    Material* MaterialProvider::makeWithShader(DxShader* shader) {
        Material* material = nullptr;
        if (shader) {
            material = ghnew Material(shader);
        }
        return material;
    }

    Material* MaterialProvider::makeBasic(ITexture* diffuseTexture) {
        Material* material = nullptr;
        IntrusivePointer<DxShader> shader(shaderProvider.loadBasic());
        if (shader!=nullptr) {
            material = ghnew Material(shader.get());
            /*if (diffuseTexture) {
                TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
                diffuse->setValue(diffuseTexture);
            }*/
        }
        return material;
    }

    Material* MaterialProvider::makeBasicLight(ITexture* diffuseTexture, ITexture* specularTexture, ITexture* normalTexture) {
        Material* material = nullptr;
        IntrusivePointer<DxShader> shader(shaderProvider.loadBasicLight());
        if (shader!=nullptr) {
            material = ghnew Material(shader.get());
            /*if (diffuseTexture) {
                TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
                diffuse->setValue(diffuseTexture);
            }
            if (specularTexture) {
                TextureParameter* specular = (TextureParameter*)material->Shader->getParameter(ParameterId::SPECULAR_TEXTURE.ConstantName);
                specular->setValue(specularTexture);
            }
            if (normalTexture) {
                TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::NORMAL_TEXTURE.ConstantName);
                diffuse->setValue(normalTexture);
            }*/
        }
        return material;
    }

    Material* MaterialProvider::makeToon(ITexture* diffuseTexture) {
        Material* material = nullptr;
        IntrusivePointer<DxShader> shader(shaderProvider.loadToon());
        if (shader!=nullptr) {
            material = ghnew Material(shader.get());
            /*if (diffuseTexture) {
                TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
                diffuse->setValue(diffuseTexture);
            }*/
        }
        return material;
    }

    Material* MaterialProvider::makeChecker() {
        Material* material = nullptr;
        IntrusivePointer<DxShader> shader(shaderProvider.loadBasic());
        if (shader!=nullptr) {
            material = ghnew Material(shader.get());
            Texture* texture = textureProvider.makeChecker();
            //TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
            //diffuse->setValue(texture);
        }
        return material;
    }

    Material* MaterialProvider::makeWireframe() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadWireframe());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeOutline() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadOutline());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeNormals() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadNormals());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeInvalid() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadInvalid());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeLightPass() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadLightPass());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeUi() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadUi());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeBasicSky() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadBasicSky());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeAdvancedSky() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadAdvancedSky());
        return makeWithShader(shader.get());
    }
}