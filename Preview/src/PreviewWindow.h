#pragma once

#include "application/SystemWindow.h"
#include "core/MathUtils.h"
#include "ui/layout/StackLayout.h"
#include "ui/control/PaddingContainer.h"
#include "ui/RootView.h"
#include "application/Application.h"
#include "ui/LayoutLoader.h"
#include "ui/style/LightTheme.h"
#include "ui/style/DarkTheme.h"
#include <ui/widget/button/CheckBox.h>

namespace Preview {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class PreviewWindow:public OverlappedWindow {
    private:
        Theme* lightTheme, *darkTheme;
        UIContext* context;
        SharedPointer<StackLayout> container;
        SharedPointer<Ghurund::UI::RootView> rootView;
        LayoutLoader layoutLoader;
        FilePath* filePath = nullptr;
        FileWatcher fileWatcher;
        std::function<void()> loadCallback;
        Application* app;

    public:
        PreviewWindow(Application& app):OverlappedWindow(app.Timer) {
            this->app = &app;
            Ghurund::SwapChain* swapChain = ghnew Ghurund::SwapChain();
            swapChain->init(app.Graphics, &app.Graphics2D, *this);
            SwapChain = swapChain;

            lightTheme = ghnew LightTheme(app.ResourceManager, app.ResourceContext, 0xff0078D7);
            darkTheme = ghnew DarkTheme(app.ResourceManager, app.ResourceContext, 0xff0078D7);
            context = ghnew UIContext(app.Graphics2D, *lightTheme, *this);
            layoutLoader.Theme = lightTheme;

            Ghurund::UI::Canvas* canvas = ghnew Ghurund::UI::Canvas();
            canvas->init(app.Graphics2D);
            rootView = ghnew Ghurund::UI::RootView(*context, *canvas);
            rootView->Theme = lightTheme;
            rootView->BackgroundColor = lightTheme->Colors[Theme::COLOR_BACKGR0UND];

            auto layout = layoutLoader.load(app.ResourceContext, L"Preview/layout.xml");
            rootView->Child = layout[0];
            container = (StackLayout*)rootView->find("container");

            RootView = rootView;
            
            DragDropEnabled = true;
            OnDropped.add([this](const Ghurund::Window& window, Array<FilePath*>* files) {
                if (files && files->Size > 0) {
                    if (filePath) {
                        fileWatcher.removeFile(*this->filePath);
                        delete this->filePath;
                    }

                    FilePath path = *files->get(0);
                    postLoadCallback(path);
                    watchFile(path);
                }
                return true;
            });
        }

        ~PreviewWindow() {
            delete filePath;
            delete context;
            delete lightTheme;
            delete darkTheme;
        }

        /*void updateTheme() {
            if (themeCheckBox->Checked) {
                rootView->BackgroundColor = darkTheme->ColorBackground;
                layoutLoader.Theme = darkTheme;
                rootView->Theme = darkTheme;
            } else {
                rootView->BackgroundColor = lightTheme->ColorBackground;
                layoutLoader.Theme = lightTheme;
                rootView->Theme = lightTheme;
            }
        }*/

        void postLoadCallback(const FilePath& path) {
            loadCallback = [this, path]() {
                File file(path);
                if (!file.Exists)
                    return;
                if (file.read() == Status::OK) {
                    loadLayout(Buffer(file.Data, file.Size));
                } else {
                    app->FunctionQueue.post(loadCallback);
                }
            };

            app->FunctionQueue.post(loadCallback);
        }

        void loadLayout(const Buffer& data) {
            PointerList<Control*> controls = layoutLoader.load(app->ResourceContext, data);
            container->Children.clear();
            for (Control* control : controls)
                container->Children.add(control);
            container->invalidate();
        }

        void watchFile(FilePath& filePath) {
            this->filePath = ghnew FilePath(filePath);
            fileWatcher.addFile(filePath, [this](const FilePath& path, const FileChange& change) {
                if (change == FileChange::RENAMED_TO || change == FileChange::MODIFIED) {
                    postLoadCallback(path);
                }
            });
        }
    };
}