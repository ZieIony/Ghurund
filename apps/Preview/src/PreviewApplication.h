#include "engine/directx/Renderer.h"
#include "core/application/Application.h"

#include "PreviewWindow.h"
#include "ThemeApplication.h"

namespace Preview {
    using namespace Ghurund::Engine;

    class PreviewApplication:public Ghurund::Core::Application, public ThemeApplication {
    protected:
        Ghurund::Engine::DirectX::Renderer renderer;
        Ghurund::Engine::ParameterManager parameterManager;

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
