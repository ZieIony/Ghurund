#include "MessengerWindow.h"

namespace Messenger {
    MessengerWindow::MessengerWindow(Application& app):OverlappedWindow(app.Timer) {
        this->app = &app;
        Ghurund::SwapChain* swapChain = ghnew Ghurund::SwapChain();
        swapChain->init(app.Graphics, &app.Graphics2D, *this);
        SwapChain = swapChain;

        theme = ghnew LightTheme(app.ResourceManager, app.ResourceContext, 0xff0078D7);
        layoutLoader.Theme = theme;
        context = ghnew UIContext(app.Graphics2D, *theme, *this);

        Ghurund::UI::Canvas* canvas = ghnew Ghurund::UI::Canvas();
        canvas->init(app.Graphics2D);
        SharedPointer<Ghurund::UI::RootView> rootView = ghnew Ghurund::UI::RootView(*context, *canvas);

        auto stack = makeShared<StackLayout>();
        stack->Alignment.vertical = Alignment::Vertical::BOTTOM;
        container = makeShared<StackLayout>();
        container->Alignment = { Alignment::Horizontal::CENTER, Alignment::Vertical::CENTER };
        auto file = makeShared<TextBlock>();
        file->Text = L"drop file here to open";
        auto padding = makeShared<PaddingContainer>(8.0f);
        padding->Child = file;
        stack->Children = { container, padding };
        rootView->Child = stack;

        rootView->Theme = theme;
        rootView->BackgroundColor = theme->ColorBackground;
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
    
    MessengerWindow::~MessengerWindow() {
        delete filePath;
        delete context;
        delete theme;
    }
    
    void MessengerWindow::postLoadCallback(const FilePath& path) {
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
    
    void MessengerWindow::loadLayout(const Buffer& data) {
        PointerList<Control*> controls = layoutLoader.load(app->ResourceContext, data);
        container->Children.clear();
        for (Control* control : controls)
            container->Children.add(control);
        container->invalidate();
    }
    
    void MessengerWindow::watchFile(FilePath& filePath) {
        this->filePath = ghnew FilePath(filePath);
        fileWatcher.addFile(filePath, [this](const FilePath& path, const FileChange& change) {
            if (change == FileChange::RENAMED_TO || change == FileChange::MODIFIED) {
                postLoadCallback(path);
            }
        });
    }
}
