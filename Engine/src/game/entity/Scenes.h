#pragma once

#include "Scene.h"
#include "graphics/Materials.h"
#include "Models.h"

namespace Ghurund {
    class Scenes {
    private:
        Scenes() = delete;

    public:
        static Scene *makeEditor(ResourceManager &resourceManager, ResourceContext &context) {
            Scene *scene = ghnew Scene();

            Material *material = Materials::makeWireframe(resourceManager, context);
            if (material) {
                Model* model = Models::makePlane(context, *material);
                if (model) {
                    model->Scale = XMFLOAT3(10000, 1, 10000);
                    scene->Entities.add(model);
                    model->release();
                }
                material->release();
            }

            return scene;
        }
    };
}