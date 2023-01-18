module;

#include "core/application/Application.h"
#include "graphics/Renderer.h"

export module Demo.DemoApplication;

import Demo.DemoWindow;

export namespace Demo {
    using namespace Ghurund;
    using namespace Ghurund::Core;

    class DemoApplication:public Application {
    protected:
        Renderer renderer;
        ParameterManager parameterManager;

    public:
        DemoApplication() {
            Features.add(std::make_unique<Graphics>());
        }

        virtual void onInit() override {
            renderer.init(Features.get<Graphics>(), parameterManager);

            auto window = ghnew DemoWindow(*this, renderer);
            window->Size = { 800, 600 };
            Windows.add(window);
            window->Visible = true;
            window->bringToFront();
        }
    };
}
