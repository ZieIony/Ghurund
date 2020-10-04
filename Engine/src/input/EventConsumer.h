#pragma once

#include "Mouse.h"
#include "Keyboard.h"
#include "core/Event.h"
#include "core/collection/List.h"

namespace Ghurund {
    class EventDispatcher {
    public:
        virtual ~EventDispatcher() {}

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) {
            return false;
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
            return false;
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
            return false;
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
            return false;
        }
    };

    class EventConsumer :public EventDispatcher {
    protected:
        Event<EventConsumer, KeyEventArgs> onKey = *this;
        Event<EventConsumer, MouseButtonEventArgs> onMouseButton = *this;
        Event<EventConsumer, MouseMotionEventArgs> onMouseMotion = *this;
        Event<EventConsumer, MouseWheelEventArgs> onMouseWheel = *this;

    public:
        virtual ~EventConsumer() {}

        inline Event<EventConsumer, KeyEventArgs>& getOnKey() {
            return onKey;
        }

        __declspec(property(get = getOnKey)) Event<EventConsumer, KeyEventArgs>& OnKey;

        inline Event<EventConsumer, MouseButtonEventArgs>& getOnMouseButton() {
            return onMouseButton;
        }

        __declspec(property(get = getOnMouseButton)) Event<EventConsumer, MouseButtonEventArgs>& OnMouseButton;

        inline Event<EventConsumer, MouseMotionEventArgs>& getOnMouseMotion() {
            return onMouseMotion;
        }

        __declspec(property(get = getOnMouseMotion)) Event<EventConsumer, MouseMotionEventArgs>& OnMouseMotion;

        inline Event<EventConsumer, MouseWheelEventArgs> getOnMouseWheel() {
            return onMouseWheel;
        }

        __declspec(property(get = getOnMouseWheel)) Event<EventConsumer, MouseWheelEventArgs>& OnMouseWheel;

        virtual bool dispatchKeyEvent(const KeyEventArgs& event) {
            return onKey(event);
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
            return OnMouseButton(event);
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
            return OnMouseMotion(event);
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& event) {
            return OnMouseWheel(event);
        }
    };
}