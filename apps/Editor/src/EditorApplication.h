#include "core/math/MathUtils.h"
#include "EditorWindow.h"
#include "ui/UIFeature.h"

namespace Ghurund::Editor {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class EditorApplication:public Application {
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
