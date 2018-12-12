#pragma once

#include "Materials.h"

namespace Ghurund {
    Material *Materials::makeChecker(ResourceManager &resourceManager, ResourceContext &context) {
        Shader *shader = Shaders::loadBasic(resourceManager, context);
        Material *material = ghnew Material(shader);
        Texture *texture = Textures::makeChecker(resourceManager, context);
        material->Textures.set("diffuse", texture);
        texture->release();
        material->Valid = true;
        return material;
    }

    Material *Materials::makeWireframe(ResourceManager &resourceManager, ResourceContext &context) {
        Shader *shader = Shaders::loadWireframe(resourceManager, context);
        Material *material = ghnew Material(shader);
        material->Valid = true;
        return material;
    }

    Material *Materials::makeNormals(ResourceManager &resourceManager, ResourceContext &context) {
        Shader *shader = Shaders::loadNormals(resourceManager, context);
        Material *material = ghnew Material(shader);
        material->Valid = true;
        return material;
    }

    Material *Materials::makeInvalid(ResourceManager &resourceManager, ResourceContext &context) {
        Shader *shader = Shaders::loadInvalid(resourceManager, context);
        Material *material = ghnew Material(shader);
        material->Valid = true;
        return material;
    }
}