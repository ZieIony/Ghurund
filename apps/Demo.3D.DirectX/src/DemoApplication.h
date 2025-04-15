#include "core/application/Application.h"

#include "DemoWindow.h"
#include "engine/directx/Renderer.h"
#include "engine/directx/Graphics.h"
#include "parameter/ParameterManager.h"

namespace Demo {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace Ghurund::Core;

    class DemoApplication:public Application {
    protected:
        Renderer renderer;
        ParameterManager parameterManager;
        DemoWindow window = DemoWindow(*this, renderer);

    public:
        DemoApplication() {
            Features.add<Graphics>();
        }

        virtual void onInit() override {
            renderer.init(Features.get<Graphics>(), parameterManager);

            window.init();
            window.closed += [this](Window& window) {
                window.Visible = false;
                quit();
                return true;
            };

            Windows.add(window);
            window.Title = _T("Demo 3D DirectX");
            window.Size = { 800, 600 };
            window.Position = { (int)window.DecorationMetrics.Left, (int)window.DecorationMetrics.Top };
            window.Visible = true;
            window.bringToFront();
        }

        virtual void onUninit() override {
            Windows.remove(window);
            window.uninit();
        }
    };
}
