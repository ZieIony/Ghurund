#pragma once

#include "Light.h"
#include "Model.h"
#include "Camera.h"
#include "GlobalEntity.h"

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

        void cull(Camera &camera) {
            XMMATRIX view = XMLoadFloat4x4(camera.getView());
            XMVECTOR determinant;
            XMMATRIX viewInv = XMMatrixInverse(&determinant, view);
            XMMATRIX proj = XMLoadFloat4x4(camera.getProj());
            BoundingFrustum frustum(proj);
            frustum.Transform(frustum, viewInv);
            for(size_t i = 0; i<models.Size; i++)
                models[i]->cull(frustum);
        }

        Model *pick(Camera &camera, XMINT2 &mousePos) {
            XMFLOAT3 pos, dir;
            camera.calcMouseRay(mousePos, pos, dir);

            List<GlobalEntity<Model>*> picked;
            for(size_t i = 0; i<models.Size; i++) {
                //if(!models[i]->Visible)
                  //  continue;
                if(models[i]->checkIntersection(pos, dir));
                    //picked.add(models[i]);
            }

            /*picked.sort([](const void *p1, const void *p2) {
                return ((GlobalEntity<Model>*)p1)
            });*/
            // TODO: get all, sort, pick closest
            return nullptr;
        }

        virtual void initParameters(ParameterManager &parameterManager) override {
            parameterWorld = parameterManager.add(Parameter::WORLD, ParameterType::MATRIX);
            parameters.add(parameterWorld);
        }

        void draw(CommandList &commandList, ParameterManager &parameterManager) {
            for(size_t i = 0; i<models.Size; i++) {
                if(!models[i]->Visible)
                    continue;

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