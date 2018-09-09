#pragma once

#include "collection/List.h"
#include "Scene.h"
#include "graphics/RenderingBatch.h"
#include "ParameterManager.h"

namespace Ghurund {
    class Level {
    private:
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

        void setScene(Scene *scene) {
            setPointer(this->scene, scene);
        }

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

    class LevelManager {
    private:
        Level *level;

    public:
        void setLevel(Level *level) {
            this->level = level;
        }

        Level *getLevel() {
            return level;
        }

        void onFrame() {

        }

        void draw(CommandList &commandList, ParameterManager &parameterManager) {
            if(level!=nullptr)
                level->draw(commandList, parameterManager);
        }
    };
}