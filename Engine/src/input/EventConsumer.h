#pragma once

#include "Ghurund.h"
#include "core/Timer.h"
#include "Mouse.h"
#include "collection/List.h"
#include "Keyboard.h"
#include "Windowsx.h"

namespace Ghurund {
	class EventDispatcher {
	public:
		virtual ~EventDispatcher() {}

		virtual bool dispatchKeyEvent(KeyEvent &event) {
			return false;
		}

		virtual bool dispatchMouseButtonEvent(MouseButtonEvent &event) {
			return false;
		}

		virtual bool dispatchMouseMotionEvent(MouseMotionEvent &event) {
			return false;
		}

		virtual bool dispatchMouseWheelEvent(MouseWheelEvent &event) {
			return false;
		}
	};

    class EventConsumer:public EventDispatcher {
	protected:
		virtual bool onKeyEvent(KeyEvent &event) {
			return false;
		}

		virtual bool onMouseButtonEvent(MouseButtonEvent &event) {
			return false;
		}

		virtual bool onMouseMouseMotionEvent(MouseMotionEvent &event) {
			return false;
		}

		virtual bool onMouseWheelEvent(MouseWheelEvent &event) {
			return false;
		}

	public:
		virtual ~EventConsumer() {}

        virtual bool dispatchKeyEvent(KeyEvent &event) {
            return onKeyEvent(event);
        }

        virtual bool dispatchMouseButtonEvent(MouseButtonEvent &event) {
            return onMouseButtonEvent(event);
        }

        virtual bool dispatchMouseMotionEvent(MouseMotionEvent &event) {
            return onMouseMouseMotionEvent(event);
        }

        virtual bool dispatchMouseWheelEvent(MouseWheelEvent &event) {
            return onMouseWheelEvent(event);
        }
    };
}