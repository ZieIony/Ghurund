#pragma once

#include "collection/List.h"
#include "Scene.h"
#include "graphics/RenderingBatch.h"
#include "ParameterManager.h"
#include "input/EventConsumer.h"

namespace Ghurund {
    class Level:public EventConsumer {
    protected:
        Camera *camera = nullptr;
        Scene *scene = nullptr;

    public:
        ~Level() {
            if(camera!=nullptr)
                camera->release();
            if(scene!=nullptr)
                scene->release();
        }

        Camera *getCamera() {
            return camera;
        }

        void setCamera(Camera *camera) {
            setPointer(this->camera, camera);
        }

        __declspec(property(get = getCamera, put = setCamera)) Camera *Camera;

        Scene *getScene() {
            return scene;
        }

        void setScene(Scene *scene) {
            setPointer(this->scene, scene);
        }

        __declspec(property(get = getScene, put = setScene)) Scene *Scene;

        virtual void onInit() {}
        virtual void onUninit() {}
        virtual void onUpdate() {}
        virtual void onPreDraw(RenderingBatch &batch) {}

        void draw(CommandList &commandList, ParameterManager &parameterManager) {
            if(camera==nullptr||scene==nullptr)
                return;

            camera->updateParameters();
            RenderingBatch batch;
            batch.initParameters(parameterManager);
            XMFLOAT4X4 identity;
            XMStoreFloat4x4(&identity, XMMatrixIdentity());
            scene->flatten(batch, identity);
            batch.cull(*camera);
            onPreDraw(batch);
            batch.draw(commandList, parameterManager);
            batch.clear();
        }
    };
}