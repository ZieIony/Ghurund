#pragma once

#include "Materials.h"
#include "game/parameter/ResourceParameter.h"

namespace Ghurund {
    Material* Materials::makeBasic(ResourceManager& resourceManager, ResourceContext& context, Texture& texture) {
        Material* material = nullptr;
        ScopedPointer<Shader> shader = Shaders::loadBasic(resourceManager, context);
        if (shader) {
            material = ghnew Material(shader);
            ResourceParameter *diffuse = (ResourceParameter*)material->Shader->getParameter("diffuseTexture");
            diffuse->setValue(&texture);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeBasicLight(ResourceManager& resourceManager, ResourceContext& context, Texture& diffuseTexture, Texture& specularTexture) {
        Material* material = nullptr;
        ScopedPointer<Shader> shader = Shaders::loadBasicLight(resourceManager, context);
        if (shader) {
            material = ghnew Material(shader);
            ResourceParameter *diffuse = (ResourceParameter*)material->Shader->getParameter("diffuseTexture");
            diffuse->setValue(&diffuseTexture);
            ResourceParameter *specular = (ResourceParameter*)material->Shader->getParameter("specularTexture");
            specular->setValue(&specularTexture);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeToon(ResourceManager& resourceManager, ResourceContext& context, Texture& texture) {
        Material* material = nullptr;
        ScopedPointer<Shader> shader = Shaders::loadToon(resourceManager, context);
        if (shader) {
            material = ghnew Material(shader);
            ResourceParameter *diffuse = (ResourceParameter*)material->Shader->getParameter("diffuseTexture");
            diffuse->setValue(&texture);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeChecker(ResourceManager& resourceManager, ResourceContext& context) {
        Material* material = nullptr;
        ScopedPointer<Shader> shader = Shaders::loadBasic(resourceManager, context);
        if (shader) {
            material = ghnew Material(shader);
            ScopedPointer<Texture> texture = Textures::makeChecker(resourceManager, context);
            ResourceParameter *diffuse = (ResourceParameter*)material->Shader->getParameter("diffuseTexture");
            diffuse->setValue(texture);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeWireframe(ResourceManager& resourceManager, ResourceContext& context) {
        Material* material = nullptr;
        ScopedPointer<Shader> shader = Shaders::loadWireframe(resourceManager, context);
        if (shader) {
            material = ghnew Material(shader);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeNormals(ResourceManager& resourceManager, ResourceContext& context) {
        Material* material = nullptr;
        ScopedPointer<Shader> shader = Shaders::loadNormals(resourceManager, context);
        if (shader) {
            material = ghnew Material(shader);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeInvalid(ResourceManager& resourceManager, ResourceContext& context) {
        Material* material = nullptr;
        ScopedPointer<Shader> shader = Shaders::loadInvalid(resourceManager, context);
        if (shader) {
            material = ghnew Material(shader);
            material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeLightPass(ResourceManager& resourceManager, ResourceContext& context) {
        Material* material = nullptr;
        ScopedPointer<Shader> shader = Shaders::loadLightPass(resourceManager, context);
        if (shader) {
            material = ghnew Material(shader);
            material->Valid = true;
        }
        return material;
    }
}