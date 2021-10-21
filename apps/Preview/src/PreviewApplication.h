#include "PreviewWindow.h"
#include "ui/UIFeature.h"

#include <format>

namespace Preview {
    class PreviewApplication:public Ghurund::Application {
    public:
        PreviewApplication() {
            Features.add<UIFeature>(ghnew UIFeature(*this));
        }

        virtual Status onInit() override {
            ResourceManager.Libraries.add(L"test", DirectoryPath(L"./test"));
     
            auto window = ghnew PreviewWindow(*this);
            Status result = window->init();
            if (result != Status::OK) {
                MessageBox(window->Handle, std::format(_T("window initialization failed with code {}"), (uint32_t)result).c_str(), _T("failed to initialize window"), MB_OK | MB_ICONERROR);
                return result;
            }
            window->Size = Settings.windowSize;
            Windows.add(window);
            window->activate();
            return Status::OK;
        }
    };
}
