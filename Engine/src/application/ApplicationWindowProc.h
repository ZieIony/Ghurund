#pragma once

#include "WindowProc.h"
#include "Application.h"
#include <string>
#include "input/Mouse.h"
#include "game/Parameter.h"

namespace Ghurund {
    class ApplicationWindowProc: public WindowProc {
    private:
        Application &app;

    public:
        ApplicationWindowProc(Application &app):app(app) {
        }

        Application &getApplication() {
            return app;
        }

        __declspec(property(get = getApplication)) Application &Application;

        void onSizeChange() {
            app.Window.updateSize();
            app.Renderer.resize(app.Graphics, app.Window.Width, app.Window.Height);
            app.Window.fillParameters();
        }

    };
}