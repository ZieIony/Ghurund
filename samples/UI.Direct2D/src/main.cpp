#include "Ghurund.Core.h"

#include "Direct2DWindow.h"
#include "core/math/Int.h"
#include "core/application/Application.h"
#include <core/io/DirectoryLibrary.h>

namespace Samples {
    class SampleApplication:public Ghurund::Core::Application {
    public:
        virtual void onInit() override {
            ResourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(L"test", DirectoryPath(L"./test")));
            ResourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(L"icons", DirectoryPath(L"./icons")));

            auto window = ghnew Direct2DWindow(this->Timer);
            window->title = _T("Preview");
            window->Size = { 800, 600 };
            Windows.add(window);
            window->visible = true;
            window->bringToFront();
        }
    };
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::main<Samples::SampleApplication>();
    return 0;
}
