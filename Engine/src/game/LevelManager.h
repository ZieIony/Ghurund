#pragma once

#include "collection/List.h"
#include "Scene.h"

namespace Ghurund {
    class Level {
    private:

    public:
        shared_ptr<Scene> scene;

        void draw(Renderer &renderer, ParameterManager &parameterManager) {
            shared_ptr<CommandList> commandList = renderer.startFrame();
            if(scene!=nullptr)
                scene->draw(commandList, parameterManager);
            renderer.finishFrame();
        }
    };

    class LevelManager {
    private:
        List<Level*> levels;

    public:
        ~LevelManager() {
            for(size_t i = 0; i<levels.Size; i++)
                delete levels[i];
        }

        void changeLevel(Level *level) {
            levels.add(level);
        }

        Level *getCurrentLevel() {
            return levels.get(0);
        }

        void onFrame() {

        }

        void draw(Renderer &renderer, ParameterManager &parameterManager) {
            getCurrentLevel()->draw(renderer, parameterManager);
        }
    };
}