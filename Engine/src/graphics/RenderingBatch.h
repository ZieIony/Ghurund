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

        Parameter *parameterWorld, *parameterWorldIT;
        Array<Parameter*> parameters;

    public:

        RenderingBatch():parameters(Array<Parameter*>(2)) {}

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

        GlobalEntity<Model> *pick(Camera &camera, XMINT2 &mousePos) {
            XMFLOAT3 pos, dir;
            camera.calcMouseRay(mousePos, pos, dir);

            List<GlobalEntity<Model>*> picked;
            for(size_t i = 0; i<models.Size; i++) {
                if(!models[i]->Visible)
                    continue;
                if(models[i]->intersects(pos, dir))
                    picked.add(models[i]);
            }

            /*picked.sort([](const void *p1, const void *p2) {
                return ((GlobalEntity<Model>*)p1)
            });*/
            // TODO: get all, sort, pick closest
            return picked.Size>0 ? picked[0] : nullptr;
        }

        virtual void initParameters(ParameterManager &parameterManager) override {
            if(parameterWorld!=nullptr)
                return;

            parameterWorld = parameterManager.add(Parameter::WORLD, ParameterType::MATRIX);
            parameterWorldIT = parameterManager.add(Parameter::WORLD_IT, ParameterType::MATRIX);
            parameters[0] = parameterWorld;
            parameters[1] = parameterWorldIT;
        }

        virtual Array<Parameter*> &getParameters() override {
            return parameters;
        }

        void draw(CommandList &commandList, ParameterManager &parameterManager) {
            for(size_t i = 0; i<models.Size; i++) {
                GlobalEntity<Model> *model = models[i];
                if(!model->Visible||!model->Entity.Valid)
                    continue;

                parameterWorld->setValue(&model->Transformation);
                XMMATRIX world = XMLoadFloat4x4(&model->Transformation);
                XMFLOAT4X4 worldIT;
                XMStoreFloat4x4(&worldIT, XMMatrixTranspose(XMMatrixInverse(nullptr, world)));
                parameterWorldIT->setValue(&worldIT);

                model->Entity.updateParameters();
                model->Entity.draw(commandList);
            }
        }

        void clear() {
            lights.clear();
            models.deleteItems();
            models.clear();
        }
    };
}