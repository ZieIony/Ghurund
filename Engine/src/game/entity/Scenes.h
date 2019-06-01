#pragma once

#include "Scene.h"
#include "graphics/Materials.h"
#include "Models.h"

namespace Ghurund {
    class Scenes {
    private:
        Scenes() = delete;

    public:
        static Scene *makeEditor(ResourceContext &context) {
            Scene *scene = ghnew Scene();

            ScopedPointer<Material> material = Materials::makeChecker(context);
            if (material) {
                ScopedPointer<Model> model = Models::makePlane(context, *material, 0);
                if (model) {
                    model->Scale = XMFLOAT3(1000, 1, 1000);
                    scene->Entities.add(model);
                }
            }

            scene->initParameters(context.ParameterManager);

            return scene;
        }
    };
}