#pragma once

#include "collection/List.h"
#include "game/parameter/ParameterManager.h"
#include "graphics/RenderStep.h"
#include "graphics/entity/Scene.h"

#include "Level.h"

namespace Ghurund {
    class LevelManager:public EventDispatcher {
    private:
        Level *level;

    public:
        ~LevelManager() {
            if(level!=nullptr)
                level->onUninit();
        }

        void setLevel(Level *level) {
            if(this->level!=nullptr)
                this->level->onUninit();
            if(level!=nullptr)
                level->onInit();
            this->level = level;
        }

        Level *getLevel() {
            return level;
        }

        virtual bool dispatchKeyEvent(KeyEventArgs &event) override {
            if(level!=nullptr)
                return level->dispatchKeyEvent(event);
            return false;
        }

        virtual bool dispatchMouseButtonEvent(MouseButtonEventArgs &event) override {
            if(level!=nullptr)
                return level->dispatchMouseButtonEvent(event);
            return false;
        }

        virtual bool dispatchMouseMotionEvent(MouseMotionEventArgs&event) override {
            if(level!=nullptr)
                return level->dispatchMouseMotionEvent(event);
            return false;
        }

        virtual bool dispatchMouseWheelEvent(MouseWheelEventArgs&event) override {
            if(level!=nullptr)
                return level->dispatchMouseWheelEvent(event);
            return false;
        }

        void update() {
            if(level!=nullptr)
                level->onUpdate();
        }

        void draw(Renderer &renderer, ParameterManager &parameterManager) {
            if(level!=nullptr)
                level->onDraw(renderer, parameterManager);
        }
    };
}