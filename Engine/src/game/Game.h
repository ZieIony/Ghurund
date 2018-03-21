#pragma once

#include "input/Input.h"

namespace Ghurund {
    class Game:public EventConsumer {
    public:
        bool onKeyEvent(KeyEvent &event) {
            if(event.getAction()==KeyAction::DOWN&&event.getKey()==VK_ESCAPE){
                PostQuitMessage(0);
            }
            return true;
        }

        bool onMouseButtonEvent(MouseButtonEvent &event) {
            return true;
        }

        bool onMouseMouseMotionEvent(MouseMotionEvent &event) {
            return true;
        }

        bool onMouseWheelEvent(MouseWheelEvent &event) {
            return true;
        }

    };
}