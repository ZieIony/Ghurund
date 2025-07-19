#pragma once

#include "core/NotNull.h"
#include "core/application/Application.h"
#include "core/application/LayerList.h"
#include "core/window/SystemWindow.h"

#include <windowsx.h>

namespace Ghurund::Core {
    template<typename T>
    class ApplicationWindow: public Ghurund::Core::SystemWindow {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE() {
            static auto PROPERTY_LAYERS = Property<ApplicationWindow, LayerList<T>&>("Layers", &getLayers);
            static auto PROPERTY_APPLICATION = Property<ApplicationWindow, Ghurund::Core::Application*>("Application", &getApplication);

            static const Ghurund::Core::Type TYPE = TypeBuilder<ApplicationWindow>()
                .withProperty(PROPERTY_LAYERS)
                .withProperty(PROPERTY_APPLICATION)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        inline static const Ghurund::Core::Type& TYPE = ApplicationWindow::GET_TYPE();
#pragma endregion

    private:
        LayerList<T> layers;
        // borrowed
        Application* app;

    protected:
        virtual bool onSizeChangedEvent() override {
            __super::onSizeChangedEvent();
            layers.Size = Size;
            return true;
        }

        virtual bool onFocusedChangedEvent() override {
            if (Focused) {
                layers.restoreFocus();
            } else {
                layers.clearFocus();
            }
            return true;
        }

    public:
        ApplicationWindow(NotNull<Application> app):SystemWindow(app->Timer), app(&app) {
            app->Windows->add(this);
        }

        ~ApplicationWindow() {
            app->Windows->remove(this);
        }

        inline LayerList<T>& getLayers() {
            return layers;
        }

        __declspec(property(get = getLayers)) LayerList<T>& Layers;

        inline Application* getApplication() {
            return app;
        }

        __declspec(property(get = getApplication)) Ghurund::Core::Application* Application;

        virtual bool onKeyEvent(const KeyEventArgs& args) override {
            return layers.dispatchKeyEvent(args);
        }

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& args) override {
            bool consumed = layers.dispatchMouseButtonEvent(args);
            if (consumed && (IsLButtonDown() || IsMButtonDown() || IsRButtonDown())) {
                SetCapture(Handle);
            } else {
                ReleaseCapture();
            }
            return consumed;
        }

        virtual bool onMouseMotionEvent(const MouseMotionEventArgs& args) override {
            return layers.dispatchMouseMotionEvent(args);
        }

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& args) override {
            return layers.dispatchMouseWheelEvent(args);
        }

        virtual void update(const uint64_t time) override {
            __super::update(time);
            layers.update(time);
        }
    };
}