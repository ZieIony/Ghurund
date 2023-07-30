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

        Ghurund::UI::DrawableFactory* drawableFactory;
        LightTheme* lightTheme = nullptr;
        DarkTheme* darkTheme = nullptr;
        Theme* currentTheme = nullptr;

    public:
        PreviewApplication();

        virtual void onInit() override;

        virtual void onUninit() override;

        virtual void setThemeType(Preview::ThemeType theme) override;

        virtual void setPrimaryColor(uint32_t color) override;

        virtual Theme& getCurrentTheme() override {
            return *currentTheme;
        }
    };
}
