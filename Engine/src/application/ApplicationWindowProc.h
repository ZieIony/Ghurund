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
        Parameter *widthParameter, *heightParameter;

    public:
        ApplicationWindowProc(Application &app):app(app) {
        }

        Application &getApplication() {
            return app;
        }

        __declspec(property(get = getApplication)) Application &Application;

        void onCreate() {
            widthParameter = app.ParameterManager.get(Parameter::WINDOW_WIDTH);
            heightParameter = app.ParameterManager.get(Parameter::WINDOW_HEIGHT);
        }

        void onSizeChange() {
            RECT rect;
            GetClientRect(app.Window.Handle, &rect);
            unsigned int width = rect.right - rect.left;
            widthParameter->setValue(&width);
            unsigned int height = rect.bottom - rect.top;
            heightParameter->setValue(&height);
        }

    };
}