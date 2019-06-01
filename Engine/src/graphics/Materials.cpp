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
        ScopedPointer<Shader> shader = Shaders::loadBasic(context);
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

    Material* Materials::makeBasicLight(ResourceContext& context, Texture* diffuseTexture, Texture* specularTexture) {
        Material* material = nullptr;
        ScopedPointer<Shader> shader = Shaders::loadBasicLight(context);
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
            material->initParameters(context.ParameterManager);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeToon(ResourceContext& context, Texture* diffuseTexture) {
        Material* material = nullptr;
        ScopedPointer<Shader> shader = Shaders::loadToon(context);
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
        ScopedPointer<Shader> shader = Shaders::loadBasic(context);
        if (shader) {
            material = ghnew Material(shader);
            ScopedPointer<Texture> texture = Textures::makeChecker(context);
            TextureParameter *diffuse = (TextureParameter*)material->Shader->getParameter(ParameterId::DIFFUSE_TEXTURE.ConstantName);
            diffuse->setValue(texture);
            material->initParameters(context.ParameterManager);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeWireframe(ResourceContext& context) {
        ScopedPointer<Shader> shader = Shaders::loadWireframe(context);
        return makeWithShader(shader, context);
    }

    Material* Materials::makeOutline(ResourceContext& context) {
        ScopedPointer<Shader> shader = Shaders::loadOutline(context);
        return makeWithShader(shader, context);
    }

    Material* Materials::makeNormals(ResourceContext& context) {
        ScopedPointer<Shader> shader = Shaders::loadNormals(context);
        return makeWithShader(shader, context);
    }

    Material* Materials::makeInvalid(ResourceContext& context) {
        ScopedPointer<Shader> shader = Shaders::loadInvalid(context);
        return makeWithShader(shader, context);
    }

    Material* Materials::makeLightPass(ResourceContext& context) {
        ScopedPointer<Shader> shader = Shaders::loadLightPass(context);
        return makeWithShader(shader, context);
    }

    Material* Materials::makeUi(ResourceContext& context) {
        ScopedPointer<Shader> shader = Shaders::loadUi(context);
        return makeWithShader(shader, context);
    }
}