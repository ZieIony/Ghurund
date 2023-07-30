#include "core/application/Application.h"
#include "graphics/Renderer.h"
#include "ui/direct2d/Graphics2D.h"

#include "ui/UIFeature.h"
#include "DemoWindow.h"
#include <ui/theme/LightTheme.h>
#include "ui/loading/DrawableFactory.h"

namespace Demo {
    using namespace Ghurund;
    using namespace Ghurund::Core;

    class DemoApplication:public Application {
    protected:
        Renderer renderer;
        ParameterManager parameterManager;
        LightTheme* theme;
        Ghurund::UI::DrawableFactory* drawableFactory;
        DemoWindow* window;

    public:
        DemoApplication() {
            auto graphics = makeShared<Graphics>();
            auto graphics2d = makeShared<UI::Direct2D::Graphics2D>(*graphics.get());
            auto uiFeature = makeShared<Ghurund::UIFeature>(*graphics2d.get(), ResourceManager);
            Features.addAll({ graphics.get(), graphics2d.get(), uiFeature.get() });
        }

        virtual void onInit() override {
            renderer.init(Features.get<Graphics>(), parameterManager);

            drawableFactory = ghnew Ghurund::UI::Direct2D::DrawableFactory(ResourceManager);
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
    };
}
