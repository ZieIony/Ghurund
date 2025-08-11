#pragma once

#include "core/application/Application.h"

#include "engine/opengl/OGlRenderer.h"
#include "engine/parameter/ParameterManager.h"

namespace Demo {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::OpenGL;
    using namespace Ghurund::Core;

    class DemoWindow;

    class DemoApplication:public Application {
    private:
        void uninitDemoApplication();

    protected:
        OGlRenderer renderer;
        ParameterManager parameterManager;
        DemoWindow* window = nullptr;

    public:
        DemoApplication() {
            //Features.add<Graphics>();
        }

        ~DemoApplication() {
            if (IsInitialized)
                uninitDemoApplication();
        }

        virtual void onInit() override;

        virtual void onUninit() override;
    };
}
