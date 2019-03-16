#pragma once

#include "Materials.h"

namespace Ghurund {
    Material* Materials::makeChecker(ResourceManager& resourceManager, ResourceContext& context) {
        Material* material = nullptr;
        Shader* shader = Shaders::loadBasic(resourceManager, context);
        if (shader) {
            material = ghnew Material(shader);
            if (material) {
                Texture* texture = Textures::makeChecker(resourceManager, context);
                material->Textures.set("diffuse", texture);
                material->Valid = true;
                if (texture)
                    texture->release();
            }
            shader->release();
        }
        return material;
    }

    Material* Materials::makeWireframe(ResourceManager& resourceManager, ResourceContext& context) {
        Material* material = nullptr;
        Shader* shader = Shaders::loadWireframe(resourceManager, context);
        if (shader) {
            material = ghnew Material(shader);
            shader->release();
            if (material)
                material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeNormals(ResourceManager& resourceManager, ResourceContext& context) {
        Material* material = nullptr;
        Shader* shader = Shaders::loadNormals(resourceManager, context);
        if (shader) {
            material = ghnew Material(shader);
            shader->release();
            if (material)
                material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeInvalid(ResourceManager& resourceManager, ResourceContext& context) {
        Material* material = nullptr;
        Shader* shader = Shaders::loadInvalid(resourceManager, context);
        if (shader) {
            material = ghnew Material(shader);
            shader->release();
            if (material)
                material->Valid = true;
        }
        return material;
    }

    Material* Materials::makeLightPass(ResourceManager& resourceManager, ResourceContext& context) {
        Material* material = nullptr;
        Shader* shader = Shaders::loadLightPass(resourceManager, context);
        if (shader) {
            material = ghnew Material(shader);
            shader->release();
            if (material)
                material->Valid = true;
        }
        return material;
    }
}