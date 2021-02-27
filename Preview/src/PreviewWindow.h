#pragma once

#include "application/SystemWindow.h"
#include "ui/RootView.h"
#include "application/Application.h"
#include "ui/LayoutLoader.h"
#include "ui/style/LightTheme.h"
#include "ui/style/DarkTheme.h"
#include <ui/widget/button/Button.h>
#include <ui/widget/button/CheckBox.h>
#include "ui/Canvas.h"

#include "LayoutBinding.h"

namespace Preview {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class PreviewWindow:public OverlappedWindow {
    private:
        Theme* lightTheme, * darkTheme;
        UIContext* context;
        SharedPointer<Ghurund::UI::RootView> rootView;
        ControlGroup* container;
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

            lightTheme = ghnew LightTheme(app.ResourceContext, 0xff0078D7);
            darkTheme = ghnew DarkTheme(app.ResourceContext, 0xff0078D7);
            context = ghnew UIContext(app.Graphics2D, *this);
            layoutLoader.init(*lightTheme, app.ResourceContext);

            Ghurund::UI::Canvas* canvas = ghnew Ghurund::UI::Canvas();
            canvas->init(app.Graphics2D);
            rootView = ghnew Ghurund::UI::RootView(*context, *canvas);
            rootView->Theme = lightTheme;
            rootView->BackgroundColor = lightTheme->Colors[Theme::COLOR_BACKGR0UND];

            PointerList<Control*> controls;
            layoutLoader.load(L"Preview/res/layout.xml", controls);
            LayoutBinding binding(controls[0]);
            rootView->Child = binding.Root;
            container = binding.Container;
            binding.ThemeCheckBox->CheckedChanged.add([this](CheckBox& checkBox) {
                updateTheme(checkBox);
                rootView->repaint();
                return true;
            });
            binding.EnabledCheckBox->CheckedChanged.add([this](CheckBox& checkBox) {
                container->Enabled = checkBox.Checked;
                container->repaint();
                return true;
            });

            auto colorClickHandler = [this](Control& control, const MouseClickedEventArgs& args) {
                ColorView* colorView = (ColorView*)control.find(ColorView::TYPE);
                darkTheme->Colors.set(Theme::COLOR_ACCENT, colorView->Color);
                darkTheme->updateColors();
                lightTheme->Colors.set(Theme::COLOR_ACCENT, colorView->Color);
                lightTheme->updateColors();
                rootView->dispatchThemeChanged();
                return true;
            };
            binding.Color1->Clicked.add(colorClickHandler);
            binding.Color2->Clicked.add(colorClickHandler);
            binding.Color3->Clicked.add(colorClickHandler);
            binding.Color4->Clicked.add(colorClickHandler);

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

        void updateTheme(CheckBox& checkBox) {
            if (checkBox.Checked) {
                rootView->BackgroundColor = darkTheme->Colors[Theme::COLOR_BACKGR0UND];
                layoutLoader.init(*darkTheme, layoutLoader.ResourceContext);
                rootView->Theme = darkTheme;
            } else {
                rootView->BackgroundColor = lightTheme->Colors[Theme::COLOR_BACKGR0UND];
                layoutLoader.init(*lightTheme, layoutLoader.ResourceContext);
                rootView->Theme = lightTheme;
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
                        loadImage(buffer);
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
            container->Children.clear();
            for (Control* control : controls)
                container->Children.add(control);
            container->invalidate();
        }

        void loadImage(const Buffer& data) {
            auto image = makeShared<BitmapImage>();
            MemoryInputStream stream(data.Data, data.Size);
            DirectoryPath baseDir(L".");
            image->load(app->ResourceContext, baseDir, stream);
            auto imageView = makeShared<ImageView>();
            imageView->Image = ghnew BitmapImageDrawable(image);
            container->Children = { imageView };
            container->invalidate();
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