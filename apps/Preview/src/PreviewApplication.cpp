#include "PreviewApplication.h"
#include <core/io/DirectoryLibrary.h>

namespace Preview {
    PreviewApplication::PreviewApplication() {
        auto graphics = makeShared<Graphics>();
        auto graphics2d = makeShared<UI::Direct2D::Graphics2D>(*graphics.get());
        auto uiFeature = makeShared<Ghurund::UIFeature>(*graphics2d.get(), ResourceManager);
        Features.addAll({ graphics.get(), graphics2d.get(), uiFeature.get() });
    }
    
    void PreviewApplication::onInit() {
        auto& uiFeature = Features.get<UIFeature>();

        drawableFactory = ghnew Ghurund::UI::Direct2D::DrawableFactory(ResourceManager);
        lightTheme = ghnew LightTheme(ResourceManager, *drawableFactory);
        darkTheme = ghnew DarkTheme(ResourceManager, *drawableFactory);
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
        delete darkTheme;
        delete lightTheme;
        delete drawableFactory;
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