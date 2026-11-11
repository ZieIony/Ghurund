#pragma once

#include "engine/application/GameApplication.h"
#include "engine/opengl/OglRenderer.h"

namespace Sample {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::OpenGL;
    using namespace Ghurund::Core;

    class SampleApplication:public GameApplication {
    private:
        OglRenderer* renderer = nullptr;
        class SampleWindow* window = nullptr;

        void uninitDemoApplication();

    protected:
        virtual void onInit() override;

        virtual void onDeinit() override;

    public:
        ~SampleApplication() {
            if (IsInitialized)
                uninitDemoApplication();
        }
    };
}
