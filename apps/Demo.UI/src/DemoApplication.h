#include "core/application/Application.h"

#include "DemoWindow.h"
#include "engine/directx/Renderer.h"
#include "parameter/ParameterManager.h"
#include "ui/directx/DxUIFeature.h"
#include "ui/theme/LightTheme.h"
#include "ui/loading/DrawableFactory.h"
#include "ui/directx/UIFeatureFactory.h"

namespace Demo {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace Ghurund::Core;
    using namespace Ghurund::UI::DirectX;

    class DemoApplication:public Application {
    protected:
        Renderer renderer;
        ParameterManager parameterManager;
        LightTheme* theme = nullptr;
        Ghurund::UI::DrawableFactory* drawableFactory = nullptr;
        DemoWindow* window = nullptr;

    public:
        DemoApplication() {
            Features->add<Graphics>();
            Features->add<UIFeature, UIFeatureFactory>();
        }

        virtual void onInit() override {
            renderer.init(Features->get<Graphics>(), parameterManager);

            drawableFactory = ghnew Ghurund::UI::DrawableFactory(ResourceManager);
            theme = ghnew LightTheme(ResourceManager, *drawableFactory);

            window = ghnew DemoWindow(*this, renderer, drawableFactory);
            window->init();
            window->closed += [this](Window& window) {
                window.Visible = false;
                quit();
                return true;
            };

            window->Position = { (int)window->DecorationMetrics.Left, (int)window->DecorationMetrics.Top };
            window->Size = { 800, 600 };
            window->Visible = true;
            window->bringToFront();
        }

        virtual void onUninit() override {
            delete window;

            delete drawableFactory;
            delete theme;
        }
    };
}
