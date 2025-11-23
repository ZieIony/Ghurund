#include "ghedxpch.h"
#include "MaterialProvider.h"

#include "engine/parameter/TextureParameter.h"
#include "engine/directx/shader/ShaderProvider.h"

namespace Ghurund::Engine::DirectX {
    DxMaterial* MaterialProvider::makeWithShader(DxShader* shader) {
        DxMaterial* material = nullptr;
        if (shader) {
            material = ghnew DxMaterial(shader);
        }
        return material;
    }

    DxMaterial* MaterialProvider::makeBasic(ITexture* diffuseTexture) {
        DxMaterial* material = nullptr;
        IntrusivePointer<DxShader> shader(shaderProvider.loadBasic());
        if (shader!=nullptr) {
            material = ghnew DxMaterial(shader.get());
            /*if (diffuseTexture) {
                TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
                diffuse->setValue(diffuseTexture);
            }*/
        }
        return material;
    }

    DxMaterial* MaterialProvider::makeBasicLight(ITexture* diffuseTexture, ITexture* specularTexture, ITexture* normalTexture) {
        DxMaterial* material = nullptr;
        IntrusivePointer<DxShader> shader(shaderProvider.loadBasicLight());
        if (shader!=nullptr) {
            material = ghnew DxMaterial(shader.get());
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

    DxMaterial* MaterialProvider::makeToon(ITexture* diffuseTexture) {
        DxMaterial* material = nullptr;
        IntrusivePointer<DxShader> shader(shaderProvider.loadToon());
        if (shader!=nullptr) {
            material = ghnew DxMaterial(shader.get());
            /*if (diffuseTexture) {
                TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
                diffuse->setValue(diffuseTexture);
            }*/
        }
        return material;
    }

    DxMaterial* MaterialProvider::makeChecker() {
        DxMaterial* material = nullptr;
        IntrusivePointer<DxShader> shader(shaderProvider.loadBasic());
        if (shader!=nullptr) {
            material = ghnew DxMaterial(shader.get());
            Texture* texture = textureProvider.makeChecker();
            //TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
            //diffuse->setValue(texture);
        }
        return material;
    }

    DxMaterial* MaterialProvider::makeWireframe() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadWireframe());
        return makeWithShader(shader.get());
    }

    DxMaterial* MaterialProvider::makeOutline() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadOutline());
        return makeWithShader(shader.get());
    }

    DxMaterial* MaterialProvider::makeNormals() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadNormals());
        return makeWithShader(shader.get());
    }

    DxMaterial* MaterialProvider::makeInvalid() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadInvalid());
        return makeWithShader(shader.get());
    }

    DxMaterial* MaterialProvider::makeLightPass() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadLightPass());
        return makeWithShader(shader.get());
    }

    DxMaterial* MaterialProvider::makeBasicSky() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadBasicSky());
        return makeWithShader(shader.get());
    }

    DxMaterial* MaterialProvider::makeAdvancedSky() {
        IntrusivePointer<DxShader> shader(shaderProvider.loadAdvancedSky());
        return makeWithShader(shader.get());
    }
}