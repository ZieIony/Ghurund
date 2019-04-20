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

            Material *material = Materials::makeChecker(resourceManager, context);
            if (material) {
                Model* model = Models::makePlane(context, *material, 5);
                if (model) {
                    model->Scale = XMFLOAT3(1000, 1, 1000);
                    scene->Entities.add(model);
                    model->release();
                }
                material->release();
            }

            return scene;
        }
    };
}