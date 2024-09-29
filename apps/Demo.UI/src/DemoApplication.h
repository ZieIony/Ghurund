#include "core/application/Application.h"

#include "DemoWindow.h"
#include "engine/directx/Renderer.h"
#include "parameter/ParameterManager.h"
#include "ui/directx/UIFeature.h"
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
            Features.add<Graphics>();
            Features.add<UIFeature, UIFeatureFactory>();
        }

        virtual void onInit() override {
            renderer.init(Features.get<Graphics>(), parameterManager);

            drawableFactory = ghnew Ghurund::UI::DrawableFactory(ResourceManager);
            theme = ghnew LightTheme(ResourceManager, *drawableFactory);

            window = ghnew DemoWindow(*this, renderer);
            window->Size = { 800, 600 };
            window->Theme = theme;
            Windows.add(window);
            window->Visible = true;
            window->bringToFront();
        }

        virtual void onUninit() override {
            delete drawableFactory;
            delete theme;
        }

        Ghurund::UI::DrawableFactory& getDrawableFactory() {
            return *drawableFactory;
        }
    };
}
