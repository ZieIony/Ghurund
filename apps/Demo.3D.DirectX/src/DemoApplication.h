#include "core/application/Application.h"

#include "DemoWindow.h"
#include "engine/directx/DxRenderer.h"
#include "engine/directx/Graphics.h"
#include "engine/parameter/ParameterManager.h"

namespace Demo {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace Ghurund::Core;

    class DemoApplication:public Application {
    protected:
        DxRenderer renderer;
        ParameterManager parameterManager;
        DemoWindow* window = nullptr;

    public:
        DemoApplication() {
            Features->add<Graphics>();
        }

        virtual void onInit() override {
            renderer.init(Features->get<Graphics>(), parameterManager);

            window = ghnew DemoWindow(*this, renderer);
            window->init();

            window->Size = { 800, 600 };
            window->Position = { (int)window->DecorationMetrics.Left, (int)window->DecorationMetrics.Top };
            window->Visible = true;
            window->bringToFront();
        }

        virtual void onUninit() override {
            delete window;
            window = nullptr;
        }
    };
}
