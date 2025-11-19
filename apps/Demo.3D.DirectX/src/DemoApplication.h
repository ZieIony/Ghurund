#pragma once

#include "core/application/Application.h"

#include "engine/directx/DxGraphics.h"
#include "engine/directx/DxRenderer.h"
#include <engine/directx/shader/DxShaderLoader.h>
#include <ui/font/Font.h>
#include <ui/font/FontLoader.h>

namespace Demo {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;

    class DemoWindow;

    class DemoApplication:public Application {
    private:
        DxRenderer* renderer = nullptr;
        DemoWindow* window = nullptr;
        IntrusivePointer<DxShaderLoader> shaderLoader;
        SharedPointer<DxShaderCompiler> shaderCompiler;
        IntrusivePointer<FontLoader> fontLoader;

        void uninitDemoApplication();

    protected:
        virtual void onInit() override;

        virtual void onUninit() override;

    public:
        DemoApplication() {
            Features.add<DxGraphics>();
            auto graphics = Features.get<DxGraphics>();

            shaderCompiler = makeShared<DxShaderCompiler>(*graphics);
            shaderLoader = makeIntrusive<DxShaderLoader>(shaderCompiler.ref());
            shaderLoader->includeDirs.add(DirectoryPath(L"./resources/shaders/DirectX/"));
            ResourceManager.Loaders.set<DxShader>(shaderLoader.ref());

            fontLoader = makeIntrusive<FontLoader>();
            ResourceManager.Loaders.set<Font>(fontLoader.ref());
        }

        ~DemoApplication() {
			if (IsInitialized)
                uninitDemoApplication();
        }
    };
}
