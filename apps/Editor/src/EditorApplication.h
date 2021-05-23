#include "EditorWindow.h"
#include "ui/UIFeature.h"

namespace Ghurund::Editor {
    class EditorApplication:public Ghurund::Application {
    public:
        EditorApplication() {
            Features.add<UIFeature>(ghnew UIFeature(*this));
        }

        void onInit() {
            auto window = ghnew EditorWindow(*this);
            window->Size = Settings.windowSize;
            Windows.add(window);
            window->activate();
        }
    };
}
