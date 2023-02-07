#include "Materials.h"

#include "parameter/TextureParameter.h"
#include "Shaders.h"

namespace Ghurund {
    Material* Materials::makeWithShader(Shader* shader, ParameterManager& parameterManager) {
        Material* material = nullptr;
        if (shader) {
            material = ghnew Material(shader);
            material->initParameters(parameterManager);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeBasic(ResourceManager& manager, ParameterManager& parameterManager, Texture* diffuseTexture) {
        Material* material = nullptr;
        SharedPointer<Shader> shader(Shaders::loadBasic(manager));
        if (shader!=nullptr) {
            material = ghnew Material(shader.get());
            /*if (diffuseTexture) {
                TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
                diffuse->setValue(diffuseTexture);
            }*/
            material->initParameters(parameterManager);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeBasicLight(ResourceManager& manager, ParameterManager& parameterManager, Texture* diffuseTexture, Texture* specularTexture, Texture* normalTexture) {
        Material* material = nullptr;
        SharedPointer<Shader> shader(Shaders::loadBasicLight(manager));
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
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeToon(ResourceManager& manager, ParameterManager& parameterManager, Texture* diffuseTexture) {
        Material* material = nullptr;
        SharedPointer<Shader> shader(Shaders::loadToon(manager));
        if (shader!=nullptr) {
            material = ghnew Material(shader.get());
            /*if (diffuseTexture) {
                TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
                diffuse->setValue(diffuseTexture);
            }*/
            material->initParameters(parameterManager);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeChecker(ResourceManager& manager, Graphics& graphics, CommandList& commandList, ParameterManager& parameterManager) {
        Material* material = nullptr;
        SharedPointer<Shader> shader(Shaders::loadBasic(manager));
        if (shader!=nullptr) {
            material = ghnew Material(shader.get());
            //SharedPointer<Texture> texture = Textures::makeChecker(graphics, commandList, manager);
            //TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
            //diffuse->setValue(texture);
            material->initParameters(parameterManager);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeWireframe(ResourceManager& manager, ParameterManager& parameterManager) {
        SharedPointer<Shader> shader(Shaders::loadWireframe(manager));
        return makeWithShader(shader.get(), parameterManager);
    }

    Material* Materials::makeOutline(ResourceManager& manager, ParameterManager& parameterManager) {
        SharedPointer<Shader> shader(Shaders::loadOutline(manager));
        return makeWithShader(shader.get(), parameterManager);
    }

    Material* Materials::makeNormals(ResourceManager& manager, ParameterManager& parameterManager) {
        SharedPointer<Shader> shader(Shaders::loadNormals(manager));
        return makeWithShader(shader.get(), parameterManager);
    }

    Material* Materials::makeInvalid(ResourceManager& manager, ParameterManager& parameterManager) {
        SharedPointer<Shader> shader(Shaders::loadInvalid(manager));
        return makeWithShader(shader.get(), parameterManager);
    }

    Material* Materials::makeLightPass(ResourceManager& manager, ParameterManager& parameterManager) {
        SharedPointer<Shader> shader(Shaders::loadLightPass(manager));
        return makeWithShader(shader.get(), parameterManager);
    }

    Material* Materials::makeUi(ResourceManager& manager, ParameterManager& parameterManager) {
        SharedPointer<Shader> shader(Shaders::loadUi(manager));
        return makeWithShader(shader.get(), parameterManager);
    }

    Material* Materials::makeBasicSky(ResourceManager& manager, ParameterManager& parameterManager) {
        SharedPointer<Shader> shader(Shaders::loadBasicSky(manager));
        return makeWithShader(shader.get(), parameterManager);
    }

    Material* Materials::makeAdvancedSky(ResourceManager& manager, ParameterManager& parameterManager) {
        SharedPointer<Shader> shader(Shaders::loadAdvancedSky(manager));
        return makeWithShader(shader.get(), parameterManager);
    }
}