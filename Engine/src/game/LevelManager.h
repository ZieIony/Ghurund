#pragma once

#include "core/collection/List.h"
#include "game/parameter/ParameterManager.h"
#include "graphics/entity/Scene.h"

#include "Level.h"

namespace Ghurund {
    class LevelManager:public EventDispatcher {
    private:
        Level* level;

    public:
        ~LevelManager() {
            if (level != nullptr)
                level->onUninit();
        }

        void setLevel(Level* level) {
            if (this->level != nullptr)
                this->level->onUninit();
            if (level != nullptr)
                level->onInit();
            this->level = level;
        }

        Level* getLevel() {
            return level;
        }

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) override {
            if (level != nullptr)
                return level->dispatchKeyEvent(event);
            return false;
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) override {
            if (level != nullptr)
                return level->dispatchMouseButtonEvent(event);
            return false;
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) override {
            if (level != nullptr)
                return level->dispatchMouseMotionEvent(event);
            return false;
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) override {
            if (level != nullptr)
                return level->dispatchMouseWheelEvent(event);
            return false;
        }

        void update() {
            if (level != nullptr)
                level->onUpdate();
        }

        void draw(CommandList& commandList) {
            if (level != nullptr)
                level->onDraw(commandList);
        }
    };
}