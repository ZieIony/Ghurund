#pragma once

#include "collection/List.h"
#include "Scene.h"

namespace Ghurund {
    class Level {
    public:
        shared_ptr<Scene> scene;

        void draw(shared_ptr<CommandList> commandList) {
            if(scene!=nullptr)
                scene->draw(commandList);
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

        void draw(shared_ptr<CommandList> commandList) {
            if(level!=nullptr)
                level->draw(commandList);
        }
    };
}