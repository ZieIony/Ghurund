#include "RenderStep.h"

namespace Ghurund {
    void RenderStep::cull() {
        XMMATRIX view = XMLoadFloat4x4(&camera->View);
        XMVECTOR determinant;
        XMMATRIX viewInv = XMMatrixInverse(&determinant, view);
        XMMATRIX proj = XMLoadFloat4x4(&camera->Projection);
        BoundingFrustum frustum(proj);
        frustum.Transform(frustum, viewInv);
        for (size_t i = 0; i < models.Size; i++)
            models[i]->cull(frustum);
    }

    Model* RenderStep::pick(XMINT2& mousePos) {
        XMFLOAT3 pos, dir;
        float dist, closestDist;
        camera->calcMouseRay(mousePos, pos, dir);

        GlobalEntity* picked = nullptr;
        for (size_t i = 0; i < models.Size; i++) {
            GlobalEntity* model = models[i];
            if (model->Culled || !model->Model.Selectable)
                continue;
            if (model->intersects(pos, dir, dist) && (picked == nullptr || dist < closestDist)) {
                picked = model;
                closestDist = dist;
            }
        }

        return picked != nullptr ? &picked->Model : nullptr;
    }

    void RenderStep::draw(Graphics& graphics, CommandList& commandList, RenderingStatistics& stats) {
#ifdef _DEBUG
        if (parameterWorld == nullptr) {
            Logger::log(LogType::ERR0R, _T("parameters not initialized, call initParameters(..) first"));
            return;
        }
#endif

        models.deleteItems();

        for (size_t i = 0; i < entities.Size; i++) {
            Entity* entity = entities[i];
            XMFLOAT4X4 identity;
            XMStoreFloat4x4(&identity, XMMatrixIdentity());
            entity->flatten(*this, identity);
        }

        camera->updateParameters();
        cull();

        if (material || invalidMaterial) {
            for (size_t i = 0; i < models.Size; i++) {
                GlobalEntity* entity = models[i];
                if (entity->Culled) {
                    stats.modelsCulled++;
                    continue;
                }

                Ghurund::Material* overrideMaterial = material;
                if (!entity->Model.Valid) {
                    if (entity->Model.Mesh != nullptr && entity->Model.Mesh->Valid
                        && entity->Model.Material != nullptr && !entity->Model.Material->Valid
                        && invalidMaterial != nullptr) {
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

                if (overrideMaterial != nullptr) {
                    Ghurund::Material* modelMaterial = entity->Model.Material;
                    modelMaterial->addReference();
                    entity->Model.Material = overrideMaterial;
                    entity->Model.updateParameters();
                    entity->Model.draw(graphics, commandList, stats);
                    entity->Model.Material = modelMaterial;
                    modelMaterial->release();
                } else {
                    entity->Model.updateParameters();
                    entity->Model.draw(graphics, commandList, stats);
                }
            }
        } else {
            for (size_t i = 0; i < models.Size; i++) {
                GlobalEntity* entity = models[i];
                if (entity->Culled) {
                    stats.modelsCulled++;
                    continue;
                }

                if (!entity->Model.Valid)
                    continue;

                parameterWorld->setValue(&entity->Transformation);
                XMMATRIX world = XMLoadFloat4x4(&entity->Transformation);
                XMFLOAT4X4 worldIT;
                XMStoreFloat4x4(&worldIT, XMMatrixTranspose(XMMatrixInverse(nullptr, world)));
                parameterWorldIT->setValue(&worldIT);

                entity->Model.updateParameters();
                entity->Model.draw(graphics, commandList, stats);
            }
        }
    }

}