#include "ui/layout/StackLayout.h"
#include "ui/control/PaddingContainer.h"
#include "ui/RootView.h"
#include "ui/LayoutLoader.h"

#include "PreviewWindow.h"

namespace Preview {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class PreviewApplication:public Application {
    public:
        void onInit() {
            SystemWindow* window = ghnew PreviewWindow(*this);

            window->initParameters(ParameterManager);

            window->Size = Settings.windowSize;

            Windows.add(window);
            window->OnClosed.add([this](Ghurund::Window& window) {
                Windows.remove((SystemWindow*)&window);
                delete &window;
                return true;
            });

            window->activate();
        }
    };
}
