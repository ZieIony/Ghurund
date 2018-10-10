#pragma once

#include "collection/List.h"
#include "Scene.h"
#include "graphics/RenderingBatch.h"
#include "ParameterManager.h"

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

        virtual void init() {}
        virtual void uninit() {}
        virtual void update() {}

        void draw(CommandList &commandList, ParameterManager &parameterManager) {
            if(camera!=nullptr)
                camera->fillParameters();
            if(scene!=nullptr) {
                RenderingBatch batch;
                XMFLOAT4X4 identity;
                XMStoreFloat4x4(&identity, XMMatrixIdentity());
                scene->flatten(batch, identity);
                batch.initParameters(parameterManager);
                batch.draw(commandList, parameterManager);
                batch.clear();
            }
        }
    };

    class LevelManager:public EventConsumer {
    private:
        Level *level;

    public:
        ~LevelManager() {
            if(level!=nullptr)
                level->uninit();
        }

        void setLevel(Level *level) {
            if(this->level!=nullptr)
                this->level->uninit();
            if(level!=nullptr)
                level->init();
            this->level = level;
        }

        Level *getLevel() {
            return level;
        }

        virtual bool dispatchKeyEvent(KeyEvent &event) override {
            if(level!=nullptr)
                return level->dispatchKeyEvent(event);
            return false;
        }

        virtual bool dispatchMouseButtonEvent(MouseButtonEvent &event) override {
            if(level!=nullptr)
                return level->dispatchMouseButtonEvent(event);
            return false;
        }

        virtual bool dispatchMouseMotionEvent(MouseMotionEvent &event) override {
            if(level!=nullptr)
                return level->dispatchMouseMotionEvent(event);
            return false;
        }

        virtual bool dispatchMouseWheelEvent(MouseWheelEvent &event) override {
            if(level!=nullptr)
                return level->dispatchMouseWheelEvent(event);
            return false;
        }

        void update() {
            if(level!=nullptr)
                level->update();
        }

        void draw(CommandList &commandList, ParameterManager &parameterManager) {
            if(level!=nullptr)
                level->draw(commandList, parameterManager);
        }
    };
}