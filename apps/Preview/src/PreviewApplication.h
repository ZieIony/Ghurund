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

        SharedPointer<Ghurund::UI::DrawableFactory> drawableFactory;
        SharedPointer<Theme> lightTheme;
        SharedPointer<Theme> darkTheme;
        SharedPointer<Theme> currentTheme;

    public:
        PreviewApplication();

        virtual void onInit() override;

        virtual void onUninit() override;

        virtual void setThemeType(Preview::ThemeType theme) override;

        virtual void setPrimaryColor(uint32_t color) override;

        virtual Theme& getCurrentTheme() override {
            return *currentTheme.get();
        }
    };
}
