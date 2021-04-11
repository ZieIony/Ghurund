#pragma once

#include "application/Application.h"
#include "application/ApplicationWindow.h"
#include "core/window/WindowClass.h"
#include "ui/LayoutLoader.h"
#include "ui/ResourceLoader.h"
#include "ui/RootView.h"
#include "ui/style/LightTheme.h"
#include "ui/style/DarkTheme.h"
#include "ui/Canvas.h"
#include "ui/UILayer.h"

#include "DemoLayout.h"

namespace Demo {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class DemoWindow:public ApplicationWindow {
    private:
        Theme* lightTheme;
        UIContext* context;
        SharedPointer<DemoLayout> demoLayout;
        SharedPointer<Ghurund::UI::RootView> rootView;
        ResourceLoader* resourceLoader;
        LayoutLoader layoutLoader;
        FileWatcher fileWatcher;
        std::function<void()> loadCallback;
        Application* app;

    public:
        DemoWindow(Application& app):ApplicationWindow(WindowClass::WINDOWED, app.Timer) {
            this->app = &app;
            Ghurund::SwapChain* swapChain = ghnew Ghurund::SwapChain();
            swapChain->init(app.Graphics, &app.Graphics2D, *this);
            SwapChain = std::unique_ptr<Ghurund::SwapChain>(swapChain);

            resourceLoader = ghnew ResourceLoader(app.ResourceContext);
            lightTheme = ghnew LightTheme(*app.Graphics2D.FontLoader, *app.Graphics2D.DWriteFactory, *resourceLoader);
            layoutLoader.init(*lightTheme, *app.Graphics2D.Factory, *resourceLoader);
            context = ghnew UIContext(*app.Graphics2D.DWriteFactory, *this, layoutLoader);

            rootView = ghnew Ghurund::UI::RootView(*context);

            PointerList<Control*> controls;
            layoutLoader.load(FilePath(L"apps/Demo.UI/res/layout.xml"), controls);
            demoLayout = ghnew DemoLayout();
            demoLayout->Theme = lightTheme;
            demoLayout->Layout = std::make_unique<LayoutBinding>(controls[0]);
            rootView->Child = demoLayout;

            Layers.add(std::unique_ptr<Layer>(ghnew UILayer(app.Graphics2D, rootView)));
        }

        ~DemoWindow() {
            Layers.clear();
            delete context;
            delete lightTheme;
            delete resourceLoader;
        }

        void loadLayout(const Buffer& data) {
            PointerList<Control*> controls;
            layoutLoader.load(data, controls);
            demoLayout->Container->Children.clear();
            for (Control* control : controls)
                demoLayout->Container->Children.add(control);
            demoLayout->Container->invalidate();
        }
    };
}