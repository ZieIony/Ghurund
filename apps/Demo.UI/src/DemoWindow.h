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
        Application* app;

    public:
        DemoWindow(Application& app):ApplicationWindow(WindowClass::WINDOWED, app.Timer) {
            this->app = &app;
            Ghurund::SwapChain* swapChain = ghnew Ghurund::SwapChain();
            swapChain->init(app.Graphics, &app.Graphics2D, *this);
            SwapChain = std::unique_ptr<Ghurund::SwapChain>(swapChain);

            app.ResourceManager.Libraries.add(L"Ghurund", FilePath(L"."));

            auto fontLoader = ghnew FontLoader(*app.Graphics2D.DWriteFactory);
            fontLoader->init();
            app.ResourceManager.registerLoader(Font::TYPE, std::unique_ptr<FontLoader>(fontLoader));
            auto imageLoader = ghnew ImageLoader();
            imageLoader->init();
            app.ResourceManager.registerLoader(Image::TYPE, std::unique_ptr<ImageLoader>(imageLoader));
            auto bitmapLoader = ghnew BitmapLoader(*imageLoader, *app.Graphics2D.DeviceContext);
            app.ResourceManager.registerLoader(Bitmap::TYPE, std::unique_ptr<BitmapLoader>(bitmapLoader));

            lightTheme = ghnew LightTheme(*app.Graphics2D.DWriteFactory, app.ResourceManager);
            context = ghnew UIContext(*app.Graphics2D.DWriteFactory, *this, app.ResourceManager);

            layoutLoader = ghnew LayoutLoader(*app.Graphics2D.Factory, app.ResourceManager, *lightTheme);
            app.ResourceManager.registerLoader(Layout::TYPE, std::unique_ptr<LayoutLoader>(layoutLoader));

            rootView = ghnew Ghurund::UI::RootView(*context);

            SharedPointer<Layout> layout = app.ResourceManager.load<Layout>(FilePath(L"apps/Demo.UI/res/layout.xml"), nullptr, LoadOption::DONT_CACHE);
            demoLayout = ghnew DemoLayout();
            demoLayout->Theme = lightTheme;
            demoLayout->Layout = std::make_unique<LayoutBinding>(layout->Controls[0]);
            rootView->Child = demoLayout;

            Layers.add(std::unique_ptr<Layer>(ghnew UILayer(app.Graphics2D, rootView)));
        }

        ~DemoWindow() {
            Layers.clear();
            delete layoutLoader;
            delete context;
            delete lightTheme;
        }

        void loadLayout(const File& file) {
            SharedPointer<Layout> layout = app->ResourceManager.load<Layout>(file);
            demoLayout->Container->Children.clear();
            for (Control* control : layout->Controls)
                demoLayout->Container->Children.add(control);
            demoLayout->Container->invalidate();
        }
    };
}