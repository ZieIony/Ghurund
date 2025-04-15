#include "Ghurund.Core.h"

#include "core/application/Application.h"
#include <core/io/DirectoryLibrary.h>
#include <core/application/ApplicationWindow.h>
#include <ui/gdi/GdiDrawingContext.h>
#include <ui/gdi/GdiUILayer.h>

namespace Samples {
    using namespace Ghurund::Core;
    using namespace Ghurund::UI::GDI;

    class SampleApplication:public Ghurund::Core::Application {
    private:
        ApplicationWindow<GdiDrawingContext> window = ApplicationWindow<GdiDrawingContext>(*this);
        GdiUiLayer* uiLayer = nullptr;

    public:
        virtual void onInit() override {
            ResourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(L"test", DirectoryPath(L"./test")));
            ResourceManager.Libraries.add(std::make_unique<DirectoryLibrary>(L"icons", DirectoryPath(L"./icons")));

            window.init();
            window.closed += [this](Window& window) {
                window.Visible = false;
                quit();
                return true;
            };

            uiLayer = ghnew GdiUiLayer();
            uiLayer->init(window);
            window.Layers.add(uiLayer);

            Windows.add(window);
            window.Title = _T("Sample UI GDI");
            window.Size = { 800, 600 };
            window.Position = { (int)window.DecorationMetrics.Left, (int)window.DecorationMetrics.Top };
            window.Visible = true;
            window.bringToFront();
        }

        virtual void onUninit() override {
            window.Layers.clear();
            delete uiLayer;
            uiLayer = nullptr;

            Windows.remove(window);
            window.uninit();

            ResourceManager.Libraries.clear();
        }
    };
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR cmdLine, int nCmdShow) {
    Ghurund::Core::main<Samples::SampleApplication>();
    return 0;
}
