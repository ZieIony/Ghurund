#pragma once

#include "core/application/Application.h"

#include "engine/directx/DxRenderer.h"
#include "engine/directx/Graphics.h"
#include "engine/parameter/ParameterManager.h"

namespace Demo {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace Ghurund::Core;

    class DemoWindow;

    class DemoApplication:public Application {
    protected:
        DxRenderer renderer;
        ParameterManager parameterManager;
        DemoWindow* window = nullptr;

    public:
        DemoApplication() {
            Features->add<Graphics>();
        }

        virtual void onInit() override;

        virtual void onUninit() override;
    };
}
