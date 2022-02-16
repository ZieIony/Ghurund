#include "EditorWindow.h"
#include "ui/UIFeature.h"
#include "core/application/Application.h"
#include "graphics/Renderer.h"

namespace Ghurund::Editor {
    class EditorApplication:public Ghurund::Core::Application {
    protected:
        Renderer renderer;
        ParameterManager parameterManager;

    public:
        EditorApplication() {
            Features.add(std::make_unique<UIFeature>(*this));
            Features.add(std::make_unique<Graphics>());
        }

        virtual void onInit() override {
            renderer.init(Features.get<Graphics>(), parameterManager);

            auto window = ghnew EditorWindow(*this, renderer);
            window->Size = { Settings.get<uint32_t>(Settings::WIDTH), Settings.get<uint32_t>(Settings::HEIGHT) };
            Windows.add(window);
            window->Visible = true;
            window->bringToFront();
        }
    };
}
