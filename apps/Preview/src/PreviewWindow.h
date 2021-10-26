#pragma once

#include "application/Application.h"
#include "application/ApplicationWindow.h"
#include "core/window/WindowClass.h"
#include "ui/Canvas.h"
#include "ui/UIFeature.h"
#include "ui/UILayer.h"
#include "ui/RootView.h"
#include "ui/layout/Layout.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/style/LightTheme.h"
#include "ui/style/DarkTheme.h"

#include "PreviewLayout.h"
#include "ui/direct2d/font/FontLoader.h"
#include "ui/direct2d/image/BitmapLoader.h"
#include "core/image/ImageLoader.h"
#include "ui/direct2d/UIContext.h"

namespace Preview {
    using namespace Ghurund;
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;
    using namespace Ghurund::UI::Direct2D;

    class PreviewWindow:public ApplicationWindow {
    private:
        Theme* lightTheme, * darkTheme;
        IUIContext* context;
        SharedPointer<PreviewLayout> previewLayout;
        SharedPointer<Ghurund::UI::RootView> rootView;
        FileWatcher fileWatcher;
        std::function<void()> loadCallback;

    public:
        PreviewWindow(Ghurund::Application& app):ApplicationWindow(WindowClass::WINDOWED, app) {}

        ~PreviewWindow() {
            Layers.clear();
            delete context;
            delete lightTheme;
            delete darkTheme;
        }

        virtual Status init() override {
            __super::init();
            UIFeature* uiFeature = Application.Features.get<UIFeature>();
            Layers.add(std::make_unique<UILayer>(uiFeature->Graphics2D, rootView, this));

            lightTheme = ghnew LightTheme(Application.ResourceManager);
            darkTheme = ghnew DarkTheme(Application.ResourceManager);
            context = ghnew UIContext(*uiFeature->Graphics2D.D2DFactory, *uiFeature->Graphics2D.DWriteFactory, uiFeature->Graphics2D.DeviceContext, *this, Application.ResourceManager);
            LayoutLoader* layoutLoader = (LayoutLoader*)Application.ResourceManager.Loaders.get<Layout>();
            layoutLoader->Theme = lightTheme;

            rootView = ghnew Ghurund::UI::RootView(*context);

            SharedPointer<Layout> layout = Application.ResourceManager.load<Layout>(FilePath(L"apps/Preview/res/layout.xml"), nullptr, LoadOption::DONT_CACHE);
            previewLayout = ghnew PreviewLayout();
            previewLayout->Theme = lightTheme;
            previewLayout->Layout = std::make_unique<LayoutBinding>(layout->Controls[0]);
            rootView->Child = previewLayout;
            previewLayout->themeChanged += [this](PreviewLayout& previewLayout, const ThemeType type) {
                updateTheme(type);
                return true;
            };

            DragDropEnabled = true;
            onDropped += [this](Ghurund::Window& window, const Array<FilePath*>& files) {
                fileWatcher.clearFiles();
                FilePath& path = *files[0];
                postLoadCallback(path);
                watchFile(path);
                return true;
            };

            return Status::OK;
        }

        void updateTheme(ThemeType type) {
            LayoutLoader* layoutLoader = (LayoutLoader*)Application.ResourceManager.Loaders.get<Layout>();
            if (type == ThemeType::Dark) {
                darkTheme->Colors.set(Theme::COLOR_ACCENT, lightTheme->Colors.get(Theme::COLOR_ACCENT));
                darkTheme->updateColors();
                layoutLoader->Theme = darkTheme;
                previewLayout->Theme = darkTheme;
            } else {
                lightTheme->Colors.set(Theme::COLOR_ACCENT, darkTheme->Colors.get(Theme::COLOR_ACCENT));
                lightTheme->updateColors();
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
                    if (path.Extension == L"xml") {
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
            SharedPointer<Layout> layout = Application.ResourceManager.load<Layout>(file, nullptr, LoadOption::DONT_CACHE);
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