#include "PreviewApplication.h"

#include "core/io/DirectoryLibrary.h"
#include "ui/direct2d/Graphics2DFactory.h"
#include <ui/direct2d/UIFeatureFactory.h>

namespace Preview {
    PreviewApplication::PreviewApplication() {
        Features.add<Graphics>();
        Features.add<Ghurund::UI::Direct2D::Graphics2D, Ghurund::UI::Direct2D::Graphics2DFactory>();
        Features.add<Ghurund::UI::Direct2D::UIFeature, Ghurund::UI::Direct2D::UIFeatureFactory>();
    }
    
    void PreviewApplication::onInit() {
        auto& uiFeature = Features.get<UIFeature>();

        drawableFactory.set(ghnew Ghurund::UI::Direct2D::DrawableFactory(ResourceManager));
        lightTheme.set(ghnew LightTheme(ResourceManager, *drawableFactory.get()));
        darkTheme.set(ghnew DarkTheme(ResourceManager, *drawableFactory.get()));
        ThemeType = ThemeType::LIGHT;

        ResourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(L"test", DirectoryPath(L"./test")));
        ResourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(L"icons", DirectoryPath(L"./icons")));

        renderer.init(Features.get<Graphics>(), parameterManager);

        auto window = ghnew PreviewWindow(*this, renderer, *this);
        window->title = _T("Preview");
        window->Size = { 800, 600 };
        Windows.add(window);
        window->visible = true;
        window->bringToFront();
    }
    
    void PreviewApplication::onUninit() {
        renderer.uninit();
        darkTheme.set(nullptr);
        lightTheme.set(nullptr);
        drawableFactory.set(nullptr);
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