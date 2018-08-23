#pragma once

#include "Light.h"
#include "Model.h"

namespace Ghurund {
    class RenderingBatch: public ParameterProvider {
    private:
        List<Light*> lights;
        List<GlobalEntity<Model>*> models;

        Parameter *parameterWorld;

    public:
        void addLight(Light &light) {
            lights.add(&light);
        }

        void addModel(GlobalEntity<Model> *model) {
            models.add(model);
        }

        virtual void initParameters(ParameterManager &parameterManager) override {
            parameterWorld = parameterManager.add(Parameter::WORLD, ParameterType::MATRIX);
            parameters.add(parameterWorld);
        }

        void draw(CommandList &commandList, ParameterManager &parameterManager) {
            for(size_t i = 0; i<models.Size; i++) {
                parameterWorld->setValue(&models[i]->getTransformation());
                models[i]->Entity.draw(commandList, parameterManager);
            }
        }

        void clear() {
            lights.clear();
            models.deleteItems();
            models.clear();
        }
    };
}