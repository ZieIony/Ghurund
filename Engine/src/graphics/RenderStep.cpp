#include "RenderStep.h"

namespace Ghurund {
    void RenderStep::cull() {
        XMMATRIX view = XMLoadFloat4x4(camera->View);
        XMVECTOR determinant;
        XMMATRIX viewInv = XMMatrixInverse(&determinant, view);
        XMMATRIX proj = XMLoadFloat4x4(camera->Projection);
        BoundingFrustum frustum(proj);
        frustum.Transform(frustum, viewInv);
        for(size_t i = 0; i<models.Size; i++)
            models[i]->cull(frustum);
    }

    GlobalEntity<Model> *RenderStep::pick(XMINT2 & mousePos) {
        XMFLOAT3 pos, dir;
        float dist, closestDist;
        camera->calcMouseRay(mousePos, pos, dir);

        GlobalEntity<Model> *picked = nullptr;
        for(size_t i = 0; i<models.Size; i++) {
            if(!models[i]->Visible)
                continue;
            if(models[i]->intersects(pos, dir, dist)&&(picked==nullptr||dist<closestDist)) {
                picked = models[i];
                closestDist = dist;
            }
        }

        return picked;
    }

    void RenderStep::draw(Graphics &graphics, CommandList & commandList, ParameterManager & parameterManager, RenderingStatistics &stats) {
        Parameter *parameterWorld = parameterManager.add(Parameter::WORLD, ParameterType::MATRIX);
        Parameter *parameterWorldIT = parameterManager.add(Parameter::WORLD_IT, ParameterType::MATRIX);

        camera->updateParameters();
        cull();

        for(size_t i = 0; i<models.Size; i++) {
            GlobalEntity<Model> *entity = models[i];
            if(!entity->Visible) {
                stats.modelsCulled++;
                continue;
            }

            Ghurund::Material *overrideMaterial = material;
            if(!entity->Entity.Valid) {
                if(entity->Entity.Mesh!=nullptr&&entity->Entity.Mesh->Valid
                   &&entity->Entity.Material!=nullptr&&!entity->Entity.Material->Valid
                   &&invalidMaterial!=nullptr) {
                    overrideMaterial = invalidMaterial;
                } else {
                    continue;
                }
            }

            parameterWorld->setValue(&entity->Transformation);
            XMMATRIX world = XMLoadFloat4x4(&entity->Transformation);
            XMFLOAT4X4 worldIT;
            XMStoreFloat4x4(&worldIT, XMMatrixTranspose(XMMatrixInverse(nullptr, world)));
            parameterWorldIT->setValue(&worldIT);

            if(overrideMaterial!=nullptr) {
                Ghurund::Material *modelMaterial = entity->Entity.Material;
                modelMaterial->addReference();
                entity->Entity.Material = overrideMaterial;
                entity->Entity.updateParameters();
                entity->Entity.draw(graphics, commandList, stats);
                entity->Entity.Material = modelMaterial;
                modelMaterial->release();
            } else {
                entity->Entity.updateParameters();
                entity->Entity.draw(graphics, commandList, stats);
            }
        }
    }
}