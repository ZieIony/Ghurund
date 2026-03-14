#pragma once

#include "Application.h"

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
        Application& app;

    protected:
        const EventHandler<Window> DEFAULT_QUIT_APP_WINDOW_CLOSED_HANDLER = [this](Window& window) {
            window.Visible = false;
            app.quit();
            return true;
        };

    public:
		ApplicationWindow(
            Application& app,
            WindowStyle style = SystemWindow::DEFAULT_WINDOW_STYLE
        ):SystemWindow(app.Timer, style), app(app) {
            app.Windows.add(*this);
        }

        ~ApplicationWindow() {
            app.Windows.remove(*this);
        }

        inline Application& getApplication() {
            return app;
        }

        __declspec(property(get = getApplication)) Ghurund::Core::Application& Application;

		virtual void fixedUpdate() {}

        virtual void update() {}
    };
}