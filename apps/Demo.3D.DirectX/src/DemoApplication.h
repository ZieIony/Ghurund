#pragma once

#include "core/application/Application.h"

#include "engine/directx/DxRenderer.h"
#include "engine/directx/DxGraphics.h"
#include "engine/parameter/ParameterManager.h"

namespace Demo {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace Ghurund::Core;

    class DemoWindow;

    class DemoApplication:public Application {
    private:
        DxRenderer* renderer = nullptr;
        ParameterManager parameterManager;
        DemoWindow* window = nullptr;

        void uninitDemoApplication();

    protected:
        virtual void onInit() override;

        virtual void onUninit() override;

    public:
        DemoApplication() {
            Features->add<DxGraphics>();
        }

        ~DemoApplication() {
			if (IsInitialized)
                uninitDemoApplication();
        }
    };
}
