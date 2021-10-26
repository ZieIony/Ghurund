#include "PreviewWindow.h"
#include "ui/UIFeature.h"

#include <format>

namespace Preview {
    class PreviewApplication:public Ghurund::Application {
    public:
        virtual Status onInit() override {
            ResourceManager.Libraries.add(L"test", DirectoryPath(L"./test"));
            ResourceManager.Libraries.add(L"icons", DirectoryPath(L"./icons"));
     
            Features.add<UIFeature>(ghnew UIFeature(*this));
            auto window = ghnew PreviewWindow(*this);
            Status result = window->init();
            if (result != Status::OK) {
                MessageBox(window->Handle, std::format(_T("window initialization failed with code {}"), (uint32_t)result).c_str(), _T("failed to initialize window"), MB_OK | MB_ICONERROR);
                return result;
            }
            window->Size = Settings.windowSize;
            Windows.add(window);
            window->Visible = true;
            window->bringToFront();
            return Status::OK;
        }
    };
}
