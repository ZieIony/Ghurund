#pragma once

#include "engine/application/GameApplication.h"
#include "engine/opengl/OglRenderer.h"
#include "engine/parameter/ParameterManager.h"

namespace Sample {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::OpenGL;
    using namespace Ghurund::Core;

    class SampleApplication:public GameApplication {
    private:
        OglRenderer* renderer = nullptr;
        ParameterManager parameterManager;
        class SampleWindow* window = nullptr;

        void uninitDemoApplication();

    protected:
        virtual void onInit() override;

        virtual void onUninit() override;

    public:
        ~SampleApplication() {
            if (IsInitialized)
                uninitDemoApplication();
        }
    };
}
