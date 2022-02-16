#include "core/math/MathUtils.h"
#include "DemoWindow.h"
#include "core/application/Application.h"
#include "graphics/Renderer.h"

namespace Demo {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class DemoApplication:public Application {
    protected:
        Renderer renderer;
        ParameterManager parameterManager;

    public:
        DemoApplication() {
            Features.add(std::make_unique<UIFeature>(*this));
            Features.add(std::make_unique<Graphics>());
        }

        virtual void onInit() override {
            renderer.init(Features.get<Graphics>(), parameterManager);

            auto window = ghnew DemoWindow(*this, renderer);
            window->Size = { Settings.get<uint32_t>("width"), Settings.get<uint32_t>("height") };
            Windows.add(window);
            window->Visible = true;
            window->bringToFront();
        }
    };
}
