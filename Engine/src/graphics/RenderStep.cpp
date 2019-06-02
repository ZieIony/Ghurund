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
            entity->queueDraw(*this, identity);
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

                Model& model = entity->Model;
                Ghurund::Material* overrideMaterial = material;
                if (!model.Valid) {
                    if (model.Mesh != nullptr && model.Mesh->Valid
                        && model.Material != nullptr && !model.Material->Valid
                        && invalidMaterial != nullptr) {
                        overrideMaterial = invalidMaterial;
                    } else {
                        continue;
                    }
                }

                setupDrawingParams(*entity);

                if (overrideMaterial != nullptr) {
                    Ghurund::Material* modelMaterial = model.Material;
                    modelMaterial->addReference();
                    model.Material = overrideMaterial;
                    model.updateParameters();
                    model.draw(graphics, commandList, stats);
                    model.Material = modelMaterial;
                    modelMaterial->release();
                } else {
                    model.updateParameters();
                    model.draw(graphics, commandList, stats);
                }
            }
        } else {
            for (size_t i = 0; i < models.Size; i++) {
                GlobalEntity* entity = models[i];
                if (entity->Culled) {
                    stats.modelsCulled++;
                    continue;
                }

                Model& model = entity->Model;
                if (!model.Valid)
                    continue;

                setupDrawingParams(*entity);

                model.updateParameters();
                model.draw(graphics, commandList, stats);
            }
        }
    }

    void RenderStep::setupDrawingParams(Ghurund::GlobalEntity& entity) {
        parameterWorld->setValue(&entity.Transformation);
        XMMATRIX world = XMLoadFloat4x4(&entity.Transformation);
        XMFLOAT4X4 worldIT;
        XMStoreFloat4x4(&worldIT, XMMatrixTranspose(XMMatrixInverse(nullptr, world)));
        parameterWorldIT->setValue(&worldIT);
    }

}