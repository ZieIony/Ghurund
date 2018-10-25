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

        void setCamera(Camera *camera) {
            setPointer(this->camera, camera);
        }

        __declspec(property(put = setCamera)) Camera *Camera;

        void setScene(Scene *scene) {
            setPointer(this->scene, scene);
        }

        __declspec(property(put = setScene)) Scene *Scene;

        virtual void onInit() {}
        virtual void onUninit() {}
        virtual void onUpdate() {}

        void draw(CommandList &commandList, ParameterManager &parameterManager) {
            if(camera==nullptr||scene==nullptr)
                return;

            camera->fillParameters();
            RenderingBatch batch;
            batch.initParameters(parameterManager);
            XMFLOAT4X4 identity;
            XMStoreFloat4x4(&identity, XMMatrixIdentity());
            scene->flatten(batch, identity);
            batch.cull(*camera);
            //batch.pick(*camera, mousePos);
            batch.draw(commandList, parameterManager);
            batch.clear();
        }
    };
}