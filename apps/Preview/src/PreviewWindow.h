#pragma once

#include "application/Application.h"
#include "application/ApplicationWindow.h"
#include "core/window/WindowClass.h"
#include "ui/Canvas.h"
#include "ui/UIFeature.h"
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
        Theme* lightTheme, * darkTheme;
        UIContext* context;
        SharedPointer<PreviewLayout> previewLayout;
        SharedPointer<Ghurund::UI::RootView> rootView;
        FileWatcher fileWatcher;
        std::function<void()> loadCallback;

    public:
        PreviewWindow(Ghurund::Application& app):ApplicationWindow(WindowClass::WINDOWED, app) {
            UIFeature* uiFeature = app.Features.get<UIFeature>();
            Graphics2D& graphics2d = uiFeature->Graphics2D;

            lightTheme = ghnew LightTheme(*graphics2d.DWriteFactory, app.ResourceManager);
            darkTheme = ghnew DarkTheme(*graphics2d.DWriteFactory, app.ResourceManager);
            context = ghnew UIContext(*graphics2d.DWriteFactory, *this, app.ResourceManager);
            uiFeature->Theme = lightTheme;

            rootView = ghnew Ghurund::UI::RootView(*context);

            SharedPointer<Layout> layout = app.ResourceManager.load<Layout>(FilePath(L"apps/Preview/res/layout.xml"), nullptr, nullptr, LoadOption::DONT_CACHE);
            previewLayout = ghnew PreviewLayout();
            previewLayout->Theme = lightTheme;
            previewLayout->Layout = std::make_unique<LayoutBinding>(layout->Controls[0]);
            rootView->Child = previewLayout;
            previewLayout->ThemeChanged.add([this](PreviewLayout& previewLayout, ThemeType type) {
                updateTheme(type);
                return true;
            });

            Layers.add(std::unique_ptr<Layer>(ghnew UILayer(graphics2d, rootView)));

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
            delete context;
            delete lightTheme;
            delete darkTheme;
        }

        void updateTheme(ThemeType type) {
            LayoutLoader* layoutLoader = (LayoutLoader*)Application.ResourceManager.Loaders.get(Layout::TYPE);
            if (type == ThemeType::Dark) {
                layoutLoader->Theme = darkTheme;
                previewLayout->Theme = darkTheme;
            } else {
                layoutLoader->Theme = lightTheme;
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
                    Application.FunctionQueue.post(loadCallback);
                }
            };

            Application.FunctionQueue.post(loadCallback);
        }

        void loadLayout(const File& file) {
            SharedPointer<Layout> layout = Application.ResourceManager.load<Layout>(file);
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