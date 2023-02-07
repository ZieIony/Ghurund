module;

#include "core/application/Application.h"
#include "core/window/WindowClass.h"
#include "ui/Canvas.h"
#include "ui/RootView.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/style/LightTheme.h"
#include "ui/style/DarkTheme.h"

#include "ui/direct2d/font/FontLoader.h"
#include "ui/direct2d/image/BitmapLoader.h"
#include "core/image/ImageLoader.h"
#include "ui/direct2d/UIContext.h"

export module Preview.PreviewWindow;

import Preview.PreviewLayout;
import Ghurund.Engine.Application.ApplicationWindow;
import Ghurund.Engine.UI.UILayer;
import Ghurund.Engine.UI.UIFeature;

export namespace Preview {
    using namespace Ghurund;
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;
    using namespace Ghurund::UI::Direct2D;

    class PreviewWindow:public ApplicationWindow {
    private:
        Theme* lightTheme = nullptr, * darkTheme = nullptr;
        SharedPointer<PreviewLayout> previewLayout;
        SharedPointer<Ghurund::UI::RootView> rootView;
        FileWatcher fileWatcher;
        std::function<void()> loadCallback;

    public:
        PreviewWindow(Ghurund::Core::Application& app, Renderer& renderer):ApplicationWindow(app, renderer) {
            Style = WindowStyle{
               .hasMinimizeButton = true,
               .hasMaximizeButton = true,
               .hasTitle = true,
               .borderStyle = WindowBorderStyle::RESIZE,
               .showOnTaskbar = true
            };
        }

        ~PreviewWindow() {
            Layers.clear();
            delete lightTheme;
            delete darkTheme;
        }

        virtual void init(WindowManager& windowManager) {
            __super::init(windowManager);

            UIFeature& uiFeature = Application.Features.get<UIFeature>();

            lightTheme = ghnew LightTheme(Application.ResourceManager);
            darkTheme = ghnew DarkTheme(Application.ResourceManager);
            LayoutLoader* layoutLoader = (LayoutLoader*)Application.ResourceManager.Loaders.get<Control>();
            layoutLoader->Theme = lightTheme;

            UILayer* uiLayer = ghnew UILayer(uiFeature.Graphics2D, *this, Application.ResourceManager);

            previewLayout.set(Application.ResourceManager.load<PreviewLayout>(FilePath(L"apps/Preview/res/layout.xml"), nullptr, LoadOption::DONT_CACHE));
            previewLayout->Theme = lightTheme;
            uiLayer->Root.Child = previewLayout.get();
            previewLayout->themeChanged += [this](PreviewLayout& previewLayout, const ThemeType type) {
                updateTheme(type);
                return true;
            };

            sizeChanged += [&](Window& window) {
                Logger::print(LogType::INFO, _T("\n"));
                Logger::print(LogType::INFO, previewLayout->printTree().Data);
                Logger::print(LogType::INFO, _T("\n"));
                return true;
            };

            DragDropEnabled = true;
            dropped += [this](Ghurund::Core::Window& window, const Array<FilePath*>& files) {
                fileWatcher.clearFiles();
                FilePath& path = *files[0];
                postLoadCallback(path);
                watchFile(path);
                return true;
            };

            Layers.add(std::unique_ptr<UILayer>(uiLayer));
        }

        void updateTheme(ThemeType type) {
            LayoutLoader* layoutLoader = (LayoutLoader*)Application.ResourceManager.Loaders.get<Control>();
            if (type == ThemeType::Dark) {
                darkTheme->Colors[Theme::COLOR_ACCENT] = lightTheme->Colors[Theme::COLOR_ACCENT];
                darkTheme->updateColors();
                layoutLoader->Theme = darkTheme;
                previewLayout->Theme = darkTheme;
            } else {
                lightTheme->Colors[Theme::COLOR_ACCENT] = darkTheme->Colors[Theme::COLOR_ACCENT];
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
            /*SharedPointer<ControlGroup> layout = Application.ResourceManager.load<ControlGroup>(file, nullptr, LoadOption::DONT_CACHE);
            previewLayout->Container->Children.clear();
            for (Control* control : layout->Children)
                previewLayout->Container->Children.add(control);
            previewLayout->Container->invalidate();*/
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