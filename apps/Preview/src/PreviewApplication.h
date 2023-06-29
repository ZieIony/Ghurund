#include "graphics/Renderer.h"
#include "core/application/Application.h"
#include "ui/direct2d/Graphics2D.h"

#include "PreviewWindow.h"
#include "ui/UIFeature.h"
#include "ThemeApplication.h"

#include <format>

namespace Preview {
    using namespace Ghurund;

    class PreviewApplication:public Ghurund::Application, public ThemeApplication {
    protected:
        Ghurund::Renderer renderer;
        Ghurund::ParameterManager parameterManager;

        LightTheme* lightTheme = nullptr;
        DarkTheme* darkTheme = nullptr;
        LayoutLoader* layoutLoader = nullptr;
        Theme* currentTheme = nullptr;

    public:
        PreviewApplication() {
            auto graphics = makeShared<Graphics>();
            auto graphics2d = makeShared<UI::Direct2D::Graphics2D>(*graphics.get());
            auto uiFeature = makeShared<Ghurund::UIFeature>(*graphics2d.get(), ResourceManager);
            Features.add(graphics.get());
            Features.add(graphics2d.get());
            Features.add(uiFeature.get());
        }

        virtual void onInit() override {
            auto& uiFeature = Features.get<UIFeature>();

            layoutLoader = &uiFeature.LayoutLoader;
            lightTheme = ghnew LightTheme(ResourceManager);
            darkTheme = ghnew DarkTheme(ResourceManager);
            ThemeType = ThemeType::LIGHT;
            
            ResourceManager.Libraries.add(L"test", DirectoryPath(L"./test"));
            ResourceManager.Libraries.add(L"icons", DirectoryPath(L"./icons"));

            renderer.init(Features.get<Graphics>(), parameterManager);

            auto window = ghnew PreviewWindow(*this, renderer, *this);
            window->title = _T("Preview");
            window->Size = { 800, 600 };
            Windows.add(window);
            window->visible = true;
            window->bringToFront();
        }

        virtual void onUninit() override {
            renderer.uninit();
            delete darkTheme;
            delete lightTheme;
        }

        virtual void setThemeType(Preview::ThemeType theme) override {
            if (theme == ThemeType::LIGHT) {
                currentTheme = lightTheme;
            } else {
                currentTheme = darkTheme;
            }
            layoutLoader->Theme = currentTheme;
        }

        virtual void setPrimaryColor(uint32_t color) override {
            lightTheme->Colors[Theme::COLOR_ACCENT].Value = color;
            lightTheme->updateColors();
            darkTheme->Colors[Theme::COLOR_ACCENT].Value = color;
            lightTheme->updateColors();
        }

        virtual Theme& getCurrentTheme() override {
            return *currentTheme;
        }
    };
}
