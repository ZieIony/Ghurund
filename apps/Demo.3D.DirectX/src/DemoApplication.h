#pragma once

#include "core/application/Application.h"
#include "engine/directx/DxGraphicsFeature.h"
#include "engine/directx/DxGraphicsFeatureFactory.h"
#include "engine/directx/DxRenderer.h"
#include "engine/directx/shader/DxShaderLoader.h"
#include "ui/font/Font.h"
#include "ui/font/FontLoader.h"
#include <ui/font/TextStyleLoader.h>

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
        IntrusivePointer<TextStyleLoader> textStyleLoader;
        IntrusivePointer<FontAtlasLoader> fontAtlasLoader;

        void uninitDemoApplication();

    protected:
        virtual void onInit() override;

        virtual void onUninit() override;

    public:
        DemoApplication() {
            Features.add<DxGraphicsFeature, DxGraphicsFeatureFactory>();
            auto graphicsFeature = Features.get<DxGraphicsFeature>();

            shaderCompiler = makeShared<DxShaderCompiler>(graphicsFeature->Graphics);
            shaderLoader = makeIntrusive<DxShaderLoader>(ResourceManager, shaderCompiler.ref());
            shaderLoader->includeDirs.add(DirectoryPath() / DirectoryPath(L"./resources/shaders/DirectX/"));
            ResourceManager.Loaders.set<DxShader>(shaderLoader.ref());

            fontLoader = makeIntrusive<FontLoader>();
            ResourceManager.Loaders.set<Font>(fontLoader.ref());
            fontAtlasLoader = makeIntrusive<FontAtlasLoader>(ResourceManager);
            ResourceManager.Loaders.set<FontAtlas>(fontAtlasLoader.ref());
            textStyleLoader = makeIntrusive<TextStyleLoader>(ResourceManager, fontAtlasLoader.ref());
            ResourceManager.Loaders.set<TextStyle>(textStyleLoader.ref());
        }

        ~DemoApplication() {
			if (IsInitialized)
                uninitDemoApplication();
        }
    };
}
