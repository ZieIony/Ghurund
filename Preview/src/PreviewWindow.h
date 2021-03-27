#pragma once

#include "application/Application.h"
#include "application/ApplicationWindow.h"
#include "core/window/WindowClass.h"
#include "ui/LayoutLoader.h"
#include "ui/ResourceLoader.h"
#include "ui/RootView.h"
#include "ui/style/LightTheme.h"
#include "ui/style/DarkTheme.h"
#include <ui/widget/button/Button.h>
#include <ui/widget/button/CheckBox.h>
#include "ui/Canvas.h"
#include "ui/UILayer.h"

#include "LayoutBinding.h"

namespace Preview {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class PreviewWindow:public ApplicationWindow {
    private:
        Theme* lightTheme, * darkTheme;
        UIContext* context;
        SharedPointer<Ghurund::UI::RootView> rootView;
        LayoutBinding* binding;
        ResourceLoader* resourceLoader;
        LayoutLoader layoutLoader;
        FilePath* filePath = nullptr;
        FileWatcher fileWatcher;
        std::function<void()> loadCallback;
        Application* app;

    public:
        PreviewWindow(Application& app):ApplicationWindow(WindowClass::WINDOWED, app.Timer) {
            this->app = &app;
            Ghurund::SwapChain* swapChain = ghnew Ghurund::SwapChain();
            swapChain->init(app.Graphics, &app.Graphics2D, *this);
            SwapChain = std::unique_ptr<Ghurund::SwapChain>(swapChain);

            resourceLoader = ghnew ResourceLoader(app.ResourceContext);
            lightTheme = ghnew LightTheme(*app.Graphics2D.FontLoader, *app.Graphics2D.DWriteFactory, *resourceLoader, 0xff0078D7);
            darkTheme = ghnew DarkTheme(*app.Graphics2D.FontLoader, *app.Graphics2D.DWriteFactory, *resourceLoader, 0xff0078D7);
            layoutLoader.init(*lightTheme, *app.Graphics2D.Factory, *resourceLoader);
            context = ghnew UIContext(*app.Graphics2D.DWriteFactory, *this, layoutLoader);

            rootView = ghnew Ghurund::UI::RootView(*context);
            rootView->Theme = lightTheme;

            PointerList<Control*> controls;
            layoutLoader.load(L"Preview/res/layout.xml", controls);
            binding = ghnew LayoutBinding(controls[0]);
            rootView->Child = binding->Root;
            binding->ThemeCheckBox->CheckedChanged.add([this](CheckBox& checkBox) {
                updateTheme(checkBox);
                rootView->repaint();
                return true;
            });
            binding->EnabledCheckBox->CheckedChanged.add([this](CheckBox& checkBox) {
                binding->Container->Enabled = checkBox.Checked;
                binding->Container->repaint();
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
            binding->Color1->Clicked.add(colorClickHandler);
            binding->Color2->Clicked.add(colorClickHandler);
            binding->Color3->Clicked.add(colorClickHandler);
            binding->Color4->Clicked.add(colorClickHandler);

            Layers.add(ghnew UILayer(app.Graphics2D, *swapChain, rootView));

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
            Layers.clear();
            delete binding;
            delete filePath;
            delete context;
            delete lightTheme;
            delete darkTheme;
            delete resourceLoader;
        }

        void updateTheme(CheckBox& checkBox) {
            if (checkBox.Checked) {
                layoutLoader.init(*darkTheme, *app->Graphics2D.Factory, *resourceLoader);
                rootView->Theme = darkTheme;
            } else {
                layoutLoader.init(*lightTheme, *app->Graphics2D.Factory, *resourceLoader);
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
            binding->Container->Children.clear();
            for (Control* control : controls)
                binding->Container->Children.add(control);
            binding->Container->invalidate();
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
            this->filePath = ghnew FilePath(filePath);
            fileWatcher.addFile(filePath, [this](const FilePath& path, const FileChange& change) {
                if (change == FileChange::RENAMED_TO || change == FileChange::MODIFIED)
                    postLoadCallback(path);
            });
        }
    };
}