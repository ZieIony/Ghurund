#pragma once

#include "Scene.h"
#include "graphics/Materials.h"
#include "TransformedEntity.h"
#include "Models.h"

namespace Ghurund {
    class Scenes {
    private:
        Scenes() = delete;

    public:
        static Scene *makeEditor(ResourceManager &resourceManager, ResourceContext &context) {
            Scene *scene = ghnew Scene();

            Material *material = Materials::makeWireframe(resourceManager, context);
            TransformedEntity *transformedModel = Models::makePlane(context, *material);
            material->release();

            transformedModel->Scale = XMFLOAT3(10000, 1, 10000);
            scene->Entities.add(transformedModel);
            transformedModel->release();

            return scene;
        }
    };
}