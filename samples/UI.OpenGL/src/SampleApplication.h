#pragma once

#include "Ghurund.Engine.OpenGL.h"

#include <engine/opengl/OGlRenderer.h>
#include "SampleWindow.h"
#include <engine/opengl/OglGraphics.h>

namespace Samples {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::OpenGL;

    class SampleApplication:public Ghurund::Core::Application {
    private:
        ParameterManager parameterManager;
        OglRenderer* renderer = nullptr;
        SampleWindow* window = nullptr;

        void uninitSampleApplication();

    protected:
        virtual void onInit() override;

        virtual void onUninit() override;

    public:
        SampleApplication() {
            Features->add<OglGraphics>();
        }

        ~SampleApplication() {
            if (IsInitialized)
                uninitSampleApplication();
        }
    };
}
