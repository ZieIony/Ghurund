#include "Ghurund.Core.h"

#include "core/application/Application.h"
#include <core/io/DirectoryLibrary.h>
#include "ui/direct2d/application/UIApplicationWindow.h"

namespace Samples {
    using namespace Ghurund::UI::Direct2D;

    class SampleApplication:public Ghurund::Core::Application {
    private:
        Renderer renderer;

    public:
        virtual void onInit() override {
            ResourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(L"test", DirectoryPath(L"./test")));
            ResourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(L"icons", DirectoryPath(L"./icons")));

            auto window = ghnew UIApplicationWindow(*this, renderer);
            window->Title = _T("Preview");
            window->Size = { 800, 600 };
            Windows.add(window);
            window->Visible = true;
            window->bringToFront();
        }
    };
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::main<Samples::SampleApplication>();
    return 0;
}
