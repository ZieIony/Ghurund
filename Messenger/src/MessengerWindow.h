#pragma once

#include "Common.h"
#include "application/SystemWindow.h"
#include "core/MathUtils.h"
#include "ui/layout/StackLayout.h"
#include "ui/control/PaddingContainer.h"
#include "ui/RootView.h"
#include "application/Application.h"
#include "ui/LayoutLoader.h"
#include "ui/style/LightTheme.h"

namespace Messenger {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class MessengerWindow:public OverlappedWindow {
    private:
        Theme* theme;
        UIContext* context;
        SharedPointer<StackLayout> container;
        LayoutLoader layoutLoader;
        FilePath* filePath = nullptr;
        FileWatcher fileWatcher;
        std::function<void()> loadCallback;
        Application* app;

    public:
        MessengerWindow(Application& app);

        ~MessengerWindow();

        void postLoadCallback(const FilePath& path);

        void loadLayout(const Buffer& data);

        void watchFile(FilePath& filePath);
    };
}