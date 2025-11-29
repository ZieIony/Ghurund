#include "PreviewApplication.h"

#include "core/io/DirectoryLibrary.h"
#include "ui/theme/DarkTheme.h"
#include "ui/theme/LightTheme.h"
#include <engine/directx/shader/DxShaderCompiler.h>
#include <engine/directx/shader/DxShaderLoader.h>
#include <ui/directx/DxUIFeature.h>
#include <ui/directx/DxUIFeatureFactory.h>

namespace Preview {
    using namespace Ghurund::UI::DirectX;

    PreviewApplication::PreviewApplication() {
        Features.add<DxGraphics>();
        auto graphics = Features.get<DxGraphics>();

        shaderCompiler = makeShared<DxShaderCompiler>(*graphics);
        auto shaderLoader = makeIntrusive<DxShaderLoader>(shaderCompiler.ref());
        shaderLoader->includeDirs.add(DirectoryPath(L"./resources/shaders/DirectX/"));
        ResourceManager.Loaders.set<DxShader>(shaderLoader.ref());

        Features.add<DxUIFeature, DxUIFeatureFactory>();
    }
    
    void PreviewApplication::onInit() {
        __super::onInit();

        auto ui = Features.get<DxUIFeature>();
        auto drawableFactory = ui->DrawableFactory;

        lightTheme.set(ghnew LightTheme(ResourceManager, *drawableFactory));
        darkTheme.set(ghnew DarkTheme(ResourceManager, *drawableFactory));
        ThemeType = ThemeType::LIGHT;

        ResourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(L"test", DirectoryPath(L"./test")));
        ResourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(L"icons", DirectoryPath(L"./icons")));

        renderer = ghnew DxRenderer(*Features.get<DxGraphics>());
        renderer->init();
        window = ghnew PreviewWindow(*this, *renderer, *this);

        window->init();
        window->Title = _T("Preview");
        window->ClientSize = { 800, 600 };
        window->Position = { 0, 0 };
        window->Visible = true;
        window->bringToFront();
    }
    
    void PreviewApplication::onUninit() {
        uninitPreviewApplication();
        __super::onUninit();
    }
    
    void PreviewApplication::setThemeType(Preview::ThemeType theme) {
        if (theme == ThemeType::LIGHT) {
            currentTheme = lightTheme;
        } else {
            currentTheme = darkTheme;
        }
    }
    
    void PreviewApplication::setPrimaryColor(uint32_t color) {
        lightTheme->Colors[Theme::COLOR_ACCENT] = color;
        lightTheme->updateColors();
        darkTheme->Colors[Theme::COLOR_ACCENT] = color;
        darkTheme->updateColors();
    }
}