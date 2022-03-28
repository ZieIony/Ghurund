module;

#include "graphics/Materials.h"

export module Ghurund.Engine.Game.Entity.Scenes;

import Ghurund.Engine.Game.Entity.Scene;

export namespace Ghurund {
    class Scenes {
    private:
        Scenes() = delete;

    public:
        static Scene *makeEditor(ResourceContext &context) {
            Scene *scene = ghnew Scene();

            /*SharedPointer<Material> material = Materials::makeChecker(context);
            if (material) {
                SharedPointer<Model> model = Models::makePlane(context, *material, 0);
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