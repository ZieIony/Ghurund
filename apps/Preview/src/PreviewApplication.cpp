#include "PreviewApplication.h"

#include "core/io/DirectoryLibrary.h"
#include "engine/directx/DxGraphicsFeatureFactory.h"
#include "ui/directx/DxUIFeatureFactory.h"
#include "ui/theme/DarkTheme.h"
#include "ui/theme/LightTheme.h"

namespace Preview {
    using namespace Ghurund::UI::DirectX;

    PreviewApplication::PreviewApplication() {
        Features.add<DxGraphicsFeature, DxGraphicsFeatureFactory>();
        Features.add<DxUIFeature, DxUIFeatureFactory>();
    }
    
    void PreviewApplication::onInit() {
        __super::onInit();

        auto ui = Features.get<DxUIFeature>();
        ui->LayoutLoader->registerType<PreviewLayout>();
        auto textureFactory = ui->TextureFactory;

        lightTheme.set(ghnew LightTheme(ResourceManager, *textureFactory));
        darkTheme.set(ghnew DarkTheme(ResourceManager, *textureFactory));
        ThemeType = ThemeType::LIGHT;

        ResourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(L"test", DirectoryPath(L"./test")));
        ResourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(L"icons", DirectoryPath(L"./icons")));

        renderer = ghnew DxRenderer(Features.get<DxGraphicsFeature>()->Graphics);
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