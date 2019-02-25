#pragma once

#include "game/entity/Light.h"
#include "game/entity/Model.h"
#include "game/entity/Camera.h"
#include "game/entity/GlobalEntity.h"
#include "graphics/RenderingStatistics.h"

namespace Ghurund {
    class RenderStep {
    private:
        PointerList<Entity*> entities;
        List<Light*> lights;
        List<GlobalEntity<Model>*> models;
        Camera* camera = nullptr;
        Material* material = nullptr;
        Material* invalidMaterial = nullptr;
        Parameter* parameterWorld;
        Parameter* parameterWorldIT;

    public:
        ~RenderStep() {
            if (camera)
                camera->release();
            if (material)
                material->release();
            if (invalidMaterial)
                invalidMaterial->release();
            models.deleteItems();
            entities.clear();
            // TODO: release all lights
        }

        PointerList<Entity*> & getEntities() {
            return entities;
        }

        __declspec(property(get = getEntities)) PointerList<Entity*> & Entities;

        void addLight(Light & light) {
            lights.add(&light);
        }

        void addModel(GlobalEntity<Model> * model) {
            models.add(model);
        }

        void setCamera(Camera * camera) {
            setPointer(this->camera, camera);
        }

        __declspec(property(put = setCamera)) Camera * Camera;

        void setMaterial(Material * material) {
            setPointer(this->material, material);
        }

        __declspec(property(put = setMaterial)) Material * Material;

        void setInvalidMaterial(Ghurund::Material * material) {
            setPointer(this->material, material);
        }

        __declspec(property(put = setInvalidMaterial)) Ghurund::Material * InvalidMaterial;

        void cull();

        Model * pick(XMINT2 & mousePos);

        void initParameters(ParameterManager & parameterManager) {
            parameterWorld = parameterManager.get(Parameter::WORLD);
            parameterWorldIT = parameterManager.get(Parameter::WORLD_IT);
        }

        void draw(Graphics & graphics, CommandList & commandList, RenderingStatistics & stats);

        void clear() {
            lights.clear();
            models.deleteItems();
            models.clear();
            if (camera) {
                camera->release();
                camera = nullptr;
            }
        }
    };
}