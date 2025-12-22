#include "engine/directx/DxRenderer.h"
#include "core/application/Application.h"

#include "PreviewWindow.h"
#include "ThemeApplication.h"

namespace Preview {
    using namespace Ghurund::Engine;

    class PreviewApplication:public Ghurund::Core::Application, public ThemeApplication {
    private:
        Ghurund::Engine::DirectX::DxRenderer* renderer = nullptr;
        PreviewWindow* window = nullptr;

        SharedPointer<Theme> lightTheme;
        SharedPointer<Theme> darkTheme;
        SharedPointer<Theme> currentTheme;

        void uninitPreviewApplication() {
            delete window;
            window = nullptr;
            delete renderer;
            renderer = nullptr;
            darkTheme.set(nullptr);
            lightTheme.set(nullptr);
            currentTheme.set(nullptr);
        }

    protected:
        virtual void onInit() override;

        virtual void onUninit() override;

    public:
        PreviewApplication();

        ~PreviewApplication() {
            if (IsInitialized)
                uninitPreviewApplication();
        }

        virtual void setThemeType(Preview::ThemeType theme) override;

        virtual void setPrimaryColor(uint32_t color) override;

        virtual Theme& getCurrentTheme() override {
            return *currentTheme.get();
        }
    };
}
