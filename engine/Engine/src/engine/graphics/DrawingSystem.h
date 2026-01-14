#pragma once

#include "DrawableComponent.h"
#include "engine/entity/camera/Camera.h"
#include "engine/entity/TransformComponent.h"
#include "engine/parameter/ValueParameter.h"
#include "material/Material.h"

namespace Ghurund::Engine {
    class DrawingSystem {
    private:
        Camera* camera = nullptr;
        Material* material = nullptr;
        Material* invalidMaterial = nullptr;
        MatrixParameter* parameterWorld = nullptr;
        MatrixParameter* parameterWorldIT = nullptr;
        RenderingStatistics stats;

    public:
        inline static const AString WORLD = "world";
        inline static const AString WORLD_IT = "worldIT";

        DrawingSystem() {
            parameterWorld = ghnew MatrixParameter(WORLD);
            parameterWorldIT = ghnew MatrixParameter(WORLD_IT);
        }

        ~DrawingSystem() {
            parameterWorld->release();
            parameterWorldIT->release();

            if (camera)
                camera->release();
            if (material)
                material->release();
            if (invalidMaterial)
                invalidMaterial->release();
        }

        inline void setCamera(Camera* camera) {
            setPointer(this->camera, camera);
        }

        inline Camera* getCamera() {
            return camera;
        }

        __declspec(property(put = setCamera, get = getCamera)) Camera* Camera;

        inline void setOverrideMaterial(Material* material) {
            setPointer(this->material, material);
        }

        __declspec(property(put = setOverrideMaterial)) Material* OverrideMaterial;

        void setInvalidMaterial(Material* invalidMaterial) {
            setPointer(this->invalidMaterial, invalidMaterial);
        }

        __declspec(property(put = setInvalidMaterial)) Material* InvalidMaterial;

        void cull() {
            XMMATRIX view = XMLoadFloat4x4(&camera->View);
            XMVECTOR determinant;
            XMMATRIX viewInv = XMMatrixInverse(&determinant, view);
            XMMATRIX proj = XMLoadFloat4x4(&camera->Projection);
            BoundingFrustum frustum(proj);
            frustum.Transform(frustum, viewInv);
            /*for (auto c : Components)
                c->cull(frustum);*/
        }

        DrawableComponent* pick(XMINT2& mousePos) {
            XMFLOAT3 pos, dir;
            //float dist, closestDist;
            camera->calcMouseRay(mousePos, pos, dir);

            DrawableComponent* picked = nullptr;
            /*for (auto c : Components) {
                if (c->Culled || !c->Selectable)
                    continue;
                if (c->intersects(pos, dir, dist) && (picked == nullptr || dist < closestDist)) {
                    picked = c;
                    closestDist = dist;
                }
            }*/

            return picked;
        }

        /*void initParameters(ParameterManager& parameterManager) {
            if (material)
                material->initParameters(parameterManager);
            if (invalidMaterial)
                invalidMaterial->initParameters(parameterManager);
            for (DrawableComponent* c : Components)
                c->initParameters(parameterManager);
        }*/

        void setupDrawingParams(TransformComponent& transform) {
            parameterWorld->setValue(transform.Transformation);
            XMMATRIX world = XMLoadFloat4x4(&transform.Transformation);
            XMFLOAT4X4 worldIT;
            XMStoreFloat4x4(&worldIT, XMMatrixTranspose(XMMatrixInverse(nullptr, world)));
            parameterWorldIT->setValue(worldIT);
        }

        /*void updateParameters(ParameterManager& parameterManager) {
            camera->updateParameters();
            parameterManager.Parameters.putAll(camera->Parameters);
        }*/

        /*void draw(CommandList& commandList) {
            cull();

            TransformComponent* t = ghnew TransformComponent();
            t->update();
            if (material || invalidMaterial) {
                for (auto c : Components) {
                    if (c->Culled) {
                        stats.modelsCulled++;
                        continue;
                    }

                    Ghurund::Material* overrideMaterial = material;
                    if (!c->Valid) {
                        if (c->Mesh != nullptr && c->Mesh->Valid
                            && c->Material != nullptr && !c->Material->Valid
                            && invalidMaterial != nullptr) {
                            overrideMaterial = invalidMaterial;
                        } else {
                            continue;
                        }
                    }

                    setupDrawingParams(*t);

                    if (overrideMaterial != nullptr) {
                        Ghurund::Material* modelMaterial = c->Material;
                        modelMaterial->addReference();
                        c->Material = overrideMaterial;
                        c->updateParameters();
                        c->draw(*graphics, commandList, stats);
                        c->Material = modelMaterial;
                        modelMaterial->release();
                    } else {
                        c->updateParameters();
                        c->draw(*graphics, commandList, stats);
                    }
                }
            } else {
                for (auto c : Components) {
                    if (c->Culled) {
                        stats.modelsCulled++;
                        continue;
                    }

                    if (!c->Valid)
                        continue;

                    setupDrawingParams(*t);

                    c->updateParameters();
                    c->draw(*graphics, commandList, stats);
                }
            }
            t->release();
        }*/

    };

}