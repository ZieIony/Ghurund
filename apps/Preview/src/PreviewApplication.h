#include "PreviewWindow.h"
#include "ui/UIFeature.h"

#include <format>

namespace Preview {
    class PreviewApplication:public Ghurund::Application {
    public:
        PreviewApplication() {
            Features.add<UIFeature>(ghnew UIFeature(*this));
        }

        virtual void onInit() override {
            ResourceManager.Libraries.add(L"test", DirectoryPath(L"./test"));
            ResourceManager.Libraries.add(L"icons", DirectoryPath(L"./icons"));

            auto window = ghnew PreviewWindow(*this);
            window->title = _T("Preview");
            window->Size = Settings.windowSize;
            Windows.add(window);
            window->visible = true;
            window->bringToFront();
        }
    };
}
