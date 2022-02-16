#pragma once

#include "application/Application.h"
#include "application/ApplicationWindow.h"
#include "core/window/WindowClass.h"
#include "ui/layout/LayoutLoader.h"
#include "ui/RootView.h"
#include "ui/style/LightTheme.h"
#include "ui/style/DarkTheme.h"
#include "ui/Canvas.h"
#include "ui/UILayer.h"

#include "DemoLayout.h"
#include "ui/font/FontLoader.h"
#include "ui/image/ImageLoader.h"
#include "ui/image/BitmapLoader.h"
#include <ui/UIFeature.h>

namespace Demo {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class DemoWindow:public ApplicationWindow {
    private:
        LayoutLoader* layoutLoader;
        Theme* lightTheme;
        UIContext* context;
        SharedPointer<DemoLayout> demoLayout;
        SharedPointer<Ghurund::UI::RootView> rootView;
        FileWatcher fileWatcher;
        std::function<void()> loadCallback;

    public:
        DemoWindow(Ghurund::Application& app, Renderer& renderer):ApplicationWindow(app, renderer) {
            Style = WindowStyle{
             .hasMinimizeButton = true,
             .hasMaximizeButton = true,
             .hasTitle = true,
             .borderStyle = WindowBorderStyle::RESIZE,
             .showOnTaskbar = true
            };
        }

        virtual void init(WindowManager& windowManager) {
            __super::init(windowManager);

            UIFeature& uiFeature = Application.Features.get<UIFeature>();
            Graphics2D& graphics2d = uiFeature.Graphics2D;

            lightTheme = ghnew LightTheme(*graphics2d.DWriteFactory, Application.ResourceManager);
            context = ghnew UIContext(*graphics2d.D2DFactory, *graphics2d.DWriteFactory, graphics2d.DeviceContext, *this, Application.ResourceManager);
            LayoutLoader* layoutLoader = (LayoutLoader*)Application.ResourceManager.Loaders.get<Control>();
            layoutLoader->Theme = lightTheme;

            rootView = ghnew Ghurund::UI::RootView(*context);

            SharedPointer<Layout> layout = app.ResourceManager.load<Layout>(FilePath(L"res/layout.xml"), nullptr, nullptr, LoadOption::DONT_CACHE);
            demoLayout = ghnew DemoLayout();
            demoLayout->Theme = lightTheme;
            demoLayout->Layout = std::make_unique<LayoutBinding>(layout->Controls[0]);
            rootView->Child = demoLayout;

            Layers.add(std::unique_ptr<Layer>(ghnew UILayer(graphics2d, rootView)));
        }

        ~DemoWindow() {
            Layers.clear();
            delete layoutLoader;
            delete context;
            delete lightTheme;
        }

        void loadLayout(const File& file) {
            SharedPointer<Control> control = Application.ResourceManager.load<Control>(file);
            demoLayout->Container->Children.clear();
            demoLayout->Container->Children.add(control);
            demoLayout->Container->invalidate();
        }
    };
}