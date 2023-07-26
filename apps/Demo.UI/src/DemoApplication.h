#include "core/application/Application.h"
#include "graphics/Renderer.h"
#include "ui/direct2d/Graphics2D.h"

#include "ui/UIFeature.h"
#include "DemoWindow.h"

namespace Demo {
    using namespace Ghurund;
    using namespace Ghurund::Core;

    class DemoApplication:public Application {
    protected:
        Renderer renderer;
        ParameterManager parameterManager;

    public:
        DemoApplication() {
            auto graphics = makeShared<Graphics>();
            auto graphics2d = makeShared<UI::Direct2D::Graphics2D>(*graphics.get());
            auto uiFeature = makeShared<Ghurund::UIFeature>(*graphics2d.get(), ResourceManager);
            Features.addAll({ graphics.get(), graphics2d.get(), uiFeature.get() });
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
