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
            SystemWindow* window = ghnew DemoWindow(*this);

            window->initParameters(ParameterManager);

            window->Size = { Settings.width, Settings.height };

            Windows.add(window);
            window->OnClosed.add([this](Ghurund::Window& window) {
                Windows.remove((SystemWindow*)&window);
                delete &window;
                return true;
            });

            window->Visible = true;
            window->activate();
        }
    };
}
