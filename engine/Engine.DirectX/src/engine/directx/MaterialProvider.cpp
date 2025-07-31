#include "ghedxpch.h"
#include "MaterialProvider.h"

#include "engine/parameter/TextureParameter.h"
#include "ShaderProvider.h"

namespace Ghurund::Engine::DirectX {
    Material* MaterialProvider::makeWithShader(Shader* shader) {
        Material* material = nullptr;
        if (shader) {
            material = ghnew Material(shader);
            material->initParameters(parameterManager);
        }
        return material;
    }

    Material* MaterialProvider::makeBasic(ITexture* diffuseTexture) {
        Material* material = nullptr;
        IntrusivePointer<Shader> shader(shaderProvider.loadBasic());
        if (shader!=nullptr) {
            material = ghnew Material(shader.get());
            /*if (diffuseTexture) {
                TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
                diffuse->setValue(diffuseTexture);
            }*/
            material->initParameters(parameterManager);
        }
        return material;
    }

    Material* MaterialProvider::makeBasicLight(ITexture* diffuseTexture, ITexture* specularTexture, ITexture* normalTexture) {
        Material* material = nullptr;
        IntrusivePointer<Shader> shader(shaderProvider.loadBasicLight());
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
            material->initParameters(parameterManager);
        }
        return material;
    }

    Material* MaterialProvider::makeToon(ITexture* diffuseTexture) {
        Material* material = nullptr;
        IntrusivePointer<Shader> shader(shaderProvider.loadToon());
        if (shader!=nullptr) {
            material = ghnew Material(shader.get());
            /*if (diffuseTexture) {
                TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
                diffuse->setValue(diffuseTexture);
            }*/
            material->initParameters(parameterManager);
        }
        return material;
    }

    Material* MaterialProvider::makeChecker() {
        Material* material = nullptr;
        IntrusivePointer<Shader> shader(shaderProvider.loadBasic());
        if (shader!=nullptr) {
            material = ghnew Material(shader.get());
            Texture* texture = textureProvider.makeChecker();
            //TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
            //diffuse->setValue(texture);
            material->initParameters(parameterManager);
        }
        return material;
    }

    Material* MaterialProvider::makeWireframe() {
        IntrusivePointer<Shader> shader(shaderProvider.loadWireframe());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeOutline() {
        IntrusivePointer<Shader> shader(shaderProvider.loadOutline());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeNormals() {
        IntrusivePointer<Shader> shader(shaderProvider.loadNormals());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeInvalid() {
        IntrusivePointer<Shader> shader(shaderProvider.loadInvalid());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeLightPass() {
        IntrusivePointer<Shader> shader(shaderProvider.loadLightPass());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeUi() {
        IntrusivePointer<Shader> shader(shaderProvider.loadUi());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeBasicSky() {
        IntrusivePointer<Shader> shader(shaderProvider.loadBasicSky());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeAdvancedSky() {
        IntrusivePointer<Shader> shader(shaderProvider.loadAdvancedSky());
        return makeWithShader(shader.get());
    }
}