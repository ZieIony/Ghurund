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
        Theme* lightTheme, * darkTheme;
        UIContext* context;
        SharedPointer<DemoLayout> previewLayout;
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
            darkTheme = ghnew DarkTheme(*app.Graphics2D.FontLoader, *app.Graphics2D.DWriteFactory, *resourceLoader);
            layoutLoader.init(*lightTheme, *app.Graphics2D.Factory, *resourceLoader);
            context = ghnew UIContext(*app.Graphics2D.DWriteFactory, *this, layoutLoader);

            rootView = ghnew Ghurund::UI::RootView(*context);

            PointerList<Control*> controls;
            layoutLoader.load(L"apps/Demo.UI/res/layout.xml", controls);
            previewLayout = ghnew DemoLayout();
            previewLayout->Theme = lightTheme;
            previewLayout->Layout = std::make_unique<LayoutBinding>(controls[0]);
            rootView->Child = previewLayout;
            previewLayout->ThemeChanged.add([this](DemoLayout& previewLayout, ThemeType type) {
                updateTheme(type);
                return true;
            });

            Layers.add(std::unique_ptr<Layer>(ghnew UILayer(app.Graphics2D, rootView)));

            DragDropEnabled = true;
            OnDropped.add([this](const Ghurund::Window& window, Array<FilePath*>& files) {
                fileWatcher.clearFiles();
                FilePath& path = *files[0];
                postLoadCallback(path);
                watchFile(path);
                return true;
            });
        }

        ~DemoWindow() {
            Layers.clear();
            delete context;
            delete lightTheme;
            delete darkTheme;
            delete resourceLoader;
        }

        void updateTheme(ThemeType type) {
            if (type == ThemeType::Dark) {
                layoutLoader.Theme = *darkTheme;
                previewLayout->Theme = darkTheme;
            } else {
                layoutLoader.Theme = *lightTheme;
                previewLayout->Theme = lightTheme;
            }
        }

        void postLoadCallback(const FilePath& path) {
            loadCallback = [this, path]() {
                File file(path);
                if (!file.Exists)
                    return;
                if (file.read() == Status::OK) {
                    layoutLoader.WorkingDirectory = path.Directory;
                    Buffer buffer(file.Data, file.Size);
                    if (path.FileName.endsWith(L".xml")) {
                        loadLayout(buffer);
                    } else {
                        loadDrawable(buffer);
                    }
                } else {
                    app->FunctionQueue.post(loadCallback);
                }
            };

            app->FunctionQueue.post(loadCallback);
        }

        void loadLayout(const Buffer& data) {
            PointerList<Control*> controls;
            layoutLoader.load(data, controls);
            previewLayout->Container->Children.clear();
            for (Control* control : controls)
                previewLayout->Container->Children.add(control);
            previewLayout->Container->invalidate();
        }

        void loadDrawable(const Buffer& data) {
            /*auto image = makeShared<BitmapImage>();
            MemoryInputStream stream(data.Data, data.Size);
            DirectoryPath baseDir(L".");
            image->load(app->ResourceContext, baseDir, stream);
            auto imageView = makeShared<ImageView>();
            imageView->Image = ghnew BitmapImageDrawable(image);
            binding->Container->Children = { imageView };
            binding->Container->invalidate();*/
        }

        void watchFile(FilePath& filePath) {
            fileWatcher.addFile(filePath, [this](const FilePath& path, const FileChange& change) {
                if (change == FileChange::RENAMED_TO || change == FileChange::MODIFIED)
                    postLoadCallback(path);
            });
        }
    };
}