#pragma once

#include "core/object/NotNull.h"
#include "core/application/Application.h"
#include "core/application/LayerList.h"
#include "core/window/SystemWindow.h"

namespace Ghurund::Core {
    class ApplicationWindow: public Ghurund::Core::SystemWindow {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ApplicationWindow::GET_TYPE();
#pragma endregion

    private:
        LayerList layers;
        // borrowed
        Application* app;

    protected:
        const EventHandler<Window> DEFAULT_QUIT_APP_WINDOW_CLOSED_HANDLER = [this](Window& window) {
            window.Visible = false;
            app->quit();
            return true;
        };

        virtual bool onSizeChangedEvent() override;

        virtual bool onFocusedChangedEvent() override;

    public:
        ApplicationWindow(NotNull<Application> app, WindowStyle style):SystemWindow(app->Timer, style), app(&app) {
            app->Windows->add(this);
        }

        ~ApplicationWindow() {
            app->Windows->remove(this);
        }

        inline LayerList& getLayers() {
            return layers;
        }

        __declspec(property(get = getLayers)) LayerList& Layers;

        inline Application* getApplication() {
            return app;
        }

        __declspec(property(get = getApplication)) Ghurund::Core::Application* Application;

        virtual bool onKeyEvent(const KeyEventArgs& args) override {
            return layers.dispatchKeyEvent(args);
        }

        virtual bool onMouseButtonEvent(const MouseButtonEventArgs& args) override;

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