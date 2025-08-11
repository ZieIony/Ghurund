#include "engine/directx/DxRenderer.h"
#include "core/application/Application.h"

#include "PreviewWindow.h"
#include "ThemeApplication.h"
#include "ui/loading/DrawableFactory.h"

namespace Preview {
    using namespace Ghurund::Engine;

    class PreviewApplication:public Ghurund::Core::Application, public ThemeApplication {
    private:
        void uninitPreviewApplication() {
            window.uninit();
            renderer.uninit();
            darkTheme.set(nullptr);
            lightTheme.set(nullptr);
        }

    protected:
        Ghurund::Engine::DirectX::DxRenderer renderer;
        Ghurund::Engine::ParameterManager parameterManager;
        PreviewWindow window = PreviewWindow(*this, renderer, *this);

        SharedPointer<Theme> lightTheme;
        SharedPointer<Theme> darkTheme;
        SharedPointer<Theme> currentTheme;

    public:
        PreviewApplication();

        ~PreviewApplication() {
            if (IsInitialized)
                uninitPreviewApplication();
        }

        virtual void onInit() override;

        virtual void onUninit() override;

        virtual void setThemeType(Preview::ThemeType theme) override;

        virtual void setPrimaryColor(uint32_t color) override;

        virtual Theme& getCurrentTheme() override {
            return *currentTheme.get();
        }
    };
}
