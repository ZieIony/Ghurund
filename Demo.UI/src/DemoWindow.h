#pragma once

#include "application/ApplicationWindow.h"
#include "core/window/WindowClass.h"
#include "ui/RootView.h"
#include "application/Application.h"
#include "ui/LayoutLoader.h"
#include "ui/style/LightTheme.h"
#include "ui/style/DarkTheme.h"
#include <ui/widget/button/Button.h>
#include <ui/widget/button/CheckBox.h>
#include <ui/widget/tab/TabContainer.h>
#include "ui/Canvas.h"
#include "ui/UILayer.h"

#include "LayoutBinding.h"
#include <DemoLayout.h>

namespace Demo {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class DemoWindow:public ApplicationWindow {
    private:
        Theme* lightTheme, * darkTheme;
        UIContext* context;
        SharedPointer<Ghurund::UI::RootView> rootView;
        TabContainer* tabs;
        LayoutLoader layoutLoader;
        FilePath* filePath = nullptr;
        FileWatcher fileWatcher;
        std::function<void()> loadCallback;
        Application* app;

    public:
        DemoWindow(Application& app):ApplicationWindow(WindowClass::WINDOWED, app.Timer) {
            this->app = &app;
            Ghurund::SwapChain* swapChain = ghnew Ghurund::SwapChain();
            swapChain->init(app.Graphics, &app.Graphics2D, *this);
            SwapChain = std::unique_ptr<Ghurund::SwapChain>(swapChain);

            lightTheme = ghnew LightTheme(app.ResourceContext, 0xff0078D7);
            darkTheme = ghnew DarkTheme(app.ResourceContext, 0xff0078D7);
            layoutLoader.init(*lightTheme, app.ResourceContext);
            context = ghnew UIContext(app.Graphics2D, *this, layoutLoader);

            Ghurund::UI::Canvas* canvas = ghnew Ghurund::UI::Canvas();
            canvas->init(app.Graphics2D.DeviceContext);
            rootView = ghnew Ghurund::UI::RootView(*context, *canvas);
            rootView->Theme = lightTheme;
            rootView->BackgroundColor = lightTheme->Colors[Theme::COLOR_BACKGR0UND];

            Layers.add(ghnew UILayer(app.Graphics2D, *swapChain, rootView));

            postLoadCallback(L"Demo.UI/res/layout.xml");
        }

        ~DemoWindow() {
            delete filePath;
            delete context;
            delete lightTheme;
            delete darkTheme;
        }

        void updateTheme(const ThemeType& themeType) {
            if (themeType == ThemeType::DARK) {
                rootView->BackgroundColor = darkTheme->Colors[Theme::COLOR_BACKGR0UND];
                layoutLoader.init(*darkTheme, layoutLoader.ResourceContext);
                rootView->Theme = darkTheme;
            } else {
                rootView->BackgroundColor = lightTheme->Colors[Theme::COLOR_BACKGR0UND];
                layoutLoader.init(*lightTheme, layoutLoader.ResourceContext);
                rootView->Theme = lightTheme;
            }
        }

        void setThemeColor(const Color& color) {
            darkTheme->Colors.set(Theme::COLOR_ACCENT, color);
            darkTheme->updateColors();
            lightTheme->Colors.set(Theme::COLOR_ACCENT, color);
            lightTheme->updateColors();
            rootView->dispatchThemeChanged();
        }

        void postLoadCallback(const FilePath& path) {
            loadCallback = [this, path]() {
                File file(path);
                if (!file.Exists)
                    return;
                if (file.read() == Status::OK) {
                    layoutLoader.WorkingDirectory = path.Directory;
                    Buffer buffer(file.Data, file.Size);
                    loadLayout(buffer);
                } else {
                    app->FunctionQueue.post(loadCallback);
                }
            };

            app->FunctionQueue.post(loadCallback);
        }

        void loadLayout(const Buffer& data) {
            PointerList<Control*> controls;
            if (layoutLoader.load(data, controls) == Status::OK) {
                auto layout = makeShared<DemoLayout>();
                layout->Layout = std::unique_ptr<LayoutBinding>(ghnew LayoutBinding(controls[0]));
                rootView->Child = layout;
                rootView->invalidate();

                layout->themeTypeChanged.add([this](DemoLayout&, const ThemeType& themeType) {
                    updateTheme(themeType);
                    rootView->repaint();
                    return true;
                });
                layout->colorChanged.add([this](DemoLayout&, const Color& color) {
                    setThemeColor(color);
                    return true;
                });
            }
        }

        void watchFile(FilePath& filePath) {
            this->filePath = ghnew FilePath(filePath);
            fileWatcher.addFile(filePath, [this](const FilePath& path, const FileChange& change) {
                if (change == FileChange::RENAMED_TO || change == FileChange::MODIFIED)
                    postLoadCallback(path);
            });
        }
    };
}