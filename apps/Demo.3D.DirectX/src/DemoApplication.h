#pragma once

#include "core/application/Application.h"

#include "engine/directx/DxRenderer.h"
#include "engine/directx/DxGraphics.h"
#include <engine/directx/shader/DxShaderLoader.h>

namespace Demo {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace Ghurund::Core;

    class DemoWindow;

    class DemoApplication:public Application {
    private:
        DxRenderer* renderer = nullptr;
        DemoWindow* window = nullptr;
        IntrusivePointer<DxShaderLoader> shaderLoader;
        SharedPointer<DxShaderCompiler> shaderCompiler;

        void uninitDemoApplication();

    protected:
        virtual void onInit() override;

        virtual void onUninit() override;

    public:
        DemoApplication() {
            Features.add<DxGraphics>();
            auto graphics = Features.get<DxGraphics>();
            shaderCompiler = makeShared<DxShaderCompiler>(*graphics);
            shaderLoader = makeIntrusive<DxShaderLoader>(*shaderCompiler.get());
            ResourceManager.Loaders.set<DxShader>(*shaderLoader.get());
        }

        ~DemoApplication() {
			if (IsInitialized)
                uninitDemoApplication();
        }
    };
}
