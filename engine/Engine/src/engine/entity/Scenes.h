#pragma once

#include "graphics/Materials.h"

#include "Scene.h"

namespace Ghurund::Engine {
    class Scenes {
    private:
        Scenes() = delete;

    public:
        static Scene *makeEditor(ResourceContext &context) {
            Scene *scene = ghnew Scene();

            /*IntrusivePointer<Material> material = Materials::makeChecker(context);
            if (material) {
                IntrusivePointer<Model> model = Models::makePlane(context, *material, 0);
                if (model) {
                    model->Scale = XMFLOAT3(1000, 1, 1000);
                    scene->Entities.add(model);
                }
            }

            scene->initParameters(context.ParameterManager);*/

            return scene;
        }
    };
}