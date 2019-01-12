#pragma once

#include "game/entity/Light.h"
#include "game/entity/Model.h"
#include "game/entity/Camera.h"
#include "game/entity/GlobalEntity.h"

namespace Ghurund {
    class RenderingBatch: public ParameterProvider {
    private:
        List<Light*> lights;
        List<GlobalEntity<Model>*> models;

        Parameter *parameterWorld = nullptr;
        Parameter *parameterWorldIT = nullptr;
        Array<Parameter*> parameters;

    public:

        RenderingBatch():parameters(Array<Parameter*>(2)) {}

        void addLight(Light &light) {
            lights.add(&light);
        }

        void addModel(GlobalEntity<Model> *model) {
            models.add(model);
        }

        void cull(Camera &camera);

        GlobalEntity<Model> *pick(Camera &camera, XMINT2 &mousePos);

        virtual void initParameters(ParameterManager &parameterManager) override;

        virtual Array<Parameter*> &getParameters() override {
            return parameters;
        }

        void draw(Graphics &graphics, CommandList &commandList, ParameterManager &parameterManager);
        void draw(Graphics &graphics, CommandList &commandList, ParameterManager &parameterManager, Material *material, Material *invalidMaterial);

        void clear() {
            lights.clear();
            models.deleteItems();
            models.clear();
        }
    };
}