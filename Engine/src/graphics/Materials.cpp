#pragma once

#include "Materials.h"
#include "game/parameter/TextureParameter.h"

namespace Ghurund {
    Material* Materials::makeWithShader(Shader* shader, ResourceContext& context) {
        Material* material = nullptr;
        if (shader) {
            material = ghnew Material(shader);
            material->initParameters(context.ParameterManager);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeBasic(ResourceContext& context, Texture* diffuseTexture) {
        Material* material = nullptr;
        SharedPointer<Shader> shader = Shaders::loadBasic(context);
        if (shader) {
            material = ghnew Material(shader);
            if (diffuseTexture) {
                TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
                diffuse->setValue(diffuseTexture);
            }
            material->initParameters(context.ParameterManager);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeBasicLight(ResourceContext& context, Texture* diffuseTexture, Texture* specularTexture, Texture* normalTexture) {
        Material* material = nullptr;
        SharedPointer<Shader> shader = Shaders::loadBasicLight(context);
        if (shader) {
            material = ghnew Material(shader);
            if (diffuseTexture) {
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
            }
            material->initParameters(context.ParameterManager);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeToon(ResourceContext& context, Texture* diffuseTexture) {
        Material* material = nullptr;
        SharedPointer<Shader> shader = Shaders::loadToon(context);
        if (shader) {
            material = ghnew Material(shader);
            if (diffuseTexture) {
                TextureParameter* diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
                diffuse->setValue(diffuseTexture);
            }
            material->initParameters(context.ParameterManager);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeChecker(ResourceContext& context) {
        Material* material = nullptr;
        SharedPointer<Shader> shader = Shaders::loadBasic(context);
        if (shader) {
            material = ghnew Material(shader);
            SharedPointer<Texture> texture = Textures::makeChecker(context);
            TextureParameter *diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
            diffuse->setValue(texture);
            material->initParameters(context.ParameterManager);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeWireframe(ResourceContext& context) {
        SharedPointer<Shader> shader = Shaders::loadWireframe(context);
        return makeWithShader(shader, context);
    }

    Material* Materials::makeOutline(ResourceContext& context) {
        SharedPointer<Shader> shader = Shaders::loadOutline(context);
        return makeWithShader(shader, context);
    }

    Material* Materials::makeNormals(ResourceContext& context) {
        SharedPointer<Shader> shader = Shaders::loadNormals(context);
        return makeWithShader(shader, context);
    }

    Material* Materials::makeInvalid(ResourceContext& context) {
        SharedPointer<Shader> shader = Shaders::loadInvalid(context);
        return makeWithShader(shader, context);
    }

    Material* Materials::makeLightPass(ResourceContext& context) {
        SharedPointer<Shader> shader = Shaders::loadLightPass(context);
        return makeWithShader(shader, context);
    }

    Material* Materials::makeUi(ResourceContext& context) {
        SharedPointer<Shader> shader = Shaders::loadUi(context);
        return makeWithShader(shader, context);
    }

	Material* Materials::makeBasicSky(ResourceContext& context) {
		SharedPointer<Shader> shader = Shaders::loadBasicSky(context);
		return makeWithShader(shader, context);
	}

	Material* Materials::makeAdvancedSky(ResourceContext& context) {
		SharedPointer<Shader> shader = Shaders::loadAdvancedSky(context);
		return makeWithShader(shader, context);
	}
}