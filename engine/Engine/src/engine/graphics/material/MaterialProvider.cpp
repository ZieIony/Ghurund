#include "ghepch.h"
#include "MaterialProvider.h"

#include "engine/parameter/TextureParameter.h"

namespace Ghurund::Engine {
    Material* MaterialProvider::makeWithShader(IShader* shader) const {
        Material* material = nullptr;
        if (shader) {
            material = ghnew Material(shader);
        }
        return material;
    }

    Material* MaterialProvider::makeBasic(ITexture* diffuseTexture) const {
        Material* material = nullptr;
        IntrusivePointer<IShader> shader(shaderProvider.loadBasic());
        if (shader!=nullptr) {
            material = ghnew Material(shader.get());
            /*if (diffuseTexture) {
                TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
                diffuse->setValue(diffuseTexture);
            }*/
        }
        return material;
    }

    Material* MaterialProvider::makeBasicLight(ITexture* diffuseTexture, ITexture* specularTexture, ITexture* normalTexture) const {
        Material* material = nullptr;
        IntrusivePointer<IShader> shader(shaderProvider.loadBasicLight());
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

    Material* MaterialProvider::makeChecker() const {
        Material* material = nullptr;
        IntrusivePointer<IShader> shader(shaderProvider.loadBasic());
        if (shader!=nullptr) {
            material = ghnew Material(shader.get());
            ITexture* texture = textureProvider.makeChecker();
            //TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
            //diffuse->setValue(texture);
        }
        return material;
    }

    Material* MaterialProvider::makeWireframe() const {
        IntrusivePointer<IShader> shader(shaderProvider.loadWireframe());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeOutline() const {
        IntrusivePointer<IShader> shader(shaderProvider.loadOutline());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeNormals() const {
        IntrusivePointer<IShader> shader(shaderProvider.loadNormals());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeInvalid() const {
        IntrusivePointer<IShader> shader(shaderProvider.loadInvalid());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeLightPass() const {
        IntrusivePointer<IShader> shader(shaderProvider.loadLightPass());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeBasicSky() const {
        IntrusivePointer<IShader> shader(shaderProvider.loadBasicSky());
        return makeWithShader(shader.get());
    }

    Material* MaterialProvider::makeAdvancedSky() const {
        IntrusivePointer<IShader> shader(shaderProvider.loadAdvancedSky());
        return makeWithShader(shader.get());
    }
}