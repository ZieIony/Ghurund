#pragma once

#include "application/Application.h"
#include "application/ApplicationWindow.h"
#include "core/window/WindowClass.h"
#include "ui/Canvas.h"
#include "ui/UILayer.h"
#include "ui/RootView.h"
#include "ui/layout/Layout.h"
#include "ui/layout/LayoutLoader.h"
#include "ui/style/LightTheme.h"
#include "ui/style/DarkTheme.h"

#include "PreviewLayout.h"
#include "ui/font/FontLoader.h"
#include "ui/image/BitmapLoader.h"
#include "ui/image/ImageLoader.h"

namespace Preview {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class PreviewWindow:public ApplicationWindow {
    private:
        LayoutLoader* layoutLoader;
        Theme* lightTheme, * darkTheme;
        UIContext* context;
        SharedPointer<PreviewLayout> previewLayout;
        SharedPointer<Ghurund::UI::RootView> rootView;
        FileWatcher fileWatcher;
        std::function<void()> loadCallback;
        Application* app;

    public:
        PreviewWindow(Application& app):ApplicationWindow(WindowClass::WINDOWED, app.Timer) {
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
            darkTheme = ghnew DarkTheme(*app.Graphics2D.DWriteFactory, app.ResourceManager);
            context = ghnew UIContext(*app.Graphics2D.DWriteFactory, *this, app.ResourceManager);

            layoutLoader = ghnew LayoutLoader(*app.Graphics2D.Factory, app.ResourceManager, *lightTheme);
            app.ResourceManager.registerLoader(Layout::TYPE, std::unique_ptr<LayoutLoader>(layoutLoader));

            rootView = ghnew Ghurund::UI::RootView(*context);

            SharedPointer<Layout> layout = app.ResourceManager.load<Layout>(FilePath(L"apps/Preview/res/layout.xml"), nullptr, LoadOption::DONT_CACHE);
            previewLayout = ghnew PreviewLayout();
            previewLayout->Theme = lightTheme;
            previewLayout->Layout = std::make_unique<LayoutBinding>(layout->Controls[0]);
            rootView->Child = previewLayout;
            previewLayout->ThemeChanged.add([this](PreviewLayout& previewLayout, ThemeType type) {
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

        ~PreviewWindow() {
            Layers.clear();
            delete layoutLoader;
            delete context;
            delete lightTheme;
            delete darkTheme;
        }

        void updateTheme(ThemeType type) {
            if (type == ThemeType::Dark) {
                layoutLoader->Theme = *darkTheme;
                previewLayout->Theme = darkTheme;
            } else {
                layoutLoader->Theme = *lightTheme;
                previewLayout->Theme = lightTheme;
            }
        }

        void postLoadCallback(const FilePath& path) {
            loadCallback = [this, path]() {
                File file(path);
                if (!file.Exists)
                    return;
                if (file.read() == Status::OK) {
                    if (path.FileName.endsWith(L".xml")) {
                        loadLayout(file);
                    } else {
                        loadDrawable(file);
                    }
                } else {
                    app->FunctionQueue.post(loadCallback);
                }
            };

            app->FunctionQueue.post(loadCallback);
        }

        void loadLayout(const File& file) {
            SharedPointer<Layout> layout = app->ResourceManager.load<Layout>(file);
            previewLayout->Container->Children.clear();
            for (Control* control : layout->Controls)
                previewLayout->Container->Children.add(control);
            previewLayout->Container->invalidate();
        }

        void loadDrawable(const File& file) {
            /*auto image = makeShared<Bitmap>();
            MemoryInputStream stream(data.Data, data.Size);
            DirectoryPath baseDir(L".");
            image->load(app->ResourceContext, baseDir, stream);
            auto imageView = makeShared<ImageView>();
            imageView->Image = ghnew BitmapDrawable(image);
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