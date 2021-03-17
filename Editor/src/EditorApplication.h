#include "core/math/MathUtils.h"
#include "ui/layout/LinearLayout.h"
#include "ui/layout/LinearLayout.h"
#include "ui/control/Space.h"
#include "ui/RootView.h"
#include "application/Application.h"
#include "application/SystemWindow.h"
#include "core/SharedPointer.h"
#include "ui/widget/menu/MenuItem.h"
#include "ui/widget/menu/Toolbar.h"
#include "ui/widget/tab/TabContainer.h"
#include "ui/widget/SplitLayout.h"
#include "tool/LogPanel.h"
#include "ui/widget/menu/PopupMenu.h"
#include "audio/Sound.h"
#include "ui/LayoutLoader.h"
#include "ui/style/LightTheme.h"

#include "control/FpsText.h"
#include "EditorWindow.h"

namespace Ghurund::Editor {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class EditorApplication:public Application {
    public:
        void onInit() {
            SystemWindow* window = ghnew EditorWindow(*this);

            window->initParameters(ParameterManager);

            window->Size = { Settings.width, Settings.height };

            Windows.add(window);
            window->OnClosed.add([this](Ghurund::Window& window) {
                Windows.remove((SystemWindow*)&window);
                delete& window;
                return true;
            });

            window->Visible = true;
            window->activate();
        }
    };
}
