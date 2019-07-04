#pragma once

#include "graphics/RenderStep.h"
#include "graphics/entity/Camera.h"
#include "application/Window.h"

namespace Ghurund {
    class GuiRenderStep:public RenderStep {
    private:
        Window& window;

    public:
        GuiRenderStep(Window& window):window(window) {
            camera = ghnew Camera();
        }
    };
}