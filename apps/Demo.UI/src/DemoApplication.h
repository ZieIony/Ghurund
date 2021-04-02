#include "core/math/MathUtils.h"
#include "ui/layout/StackLayout.h"
#include "ui/control/PaddingContainer.h"
#include "ui/RootView.h"
#include "ui/LayoutLoader.h"

#include "DemoWindow.h"

namespace Demo {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class DemoApplication:public Application {
    public:
        void onInit() {
            ApplicationWindow* window = ghnew DemoWindow(*this);
            window->Size = Settings.windowSize;
            Windows.add(window);
            window->activate();
        }
    };
}
