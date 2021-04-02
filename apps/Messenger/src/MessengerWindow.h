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
#include "net/Server.h"
#include "net/Client.h"

namespace Messenger {
    using namespace Ghurund;
    using namespace Ghurund::UI;
    using namespace Ghurund::Net;

    class MessengerWindow:public OverlappedWindow {
    private:
        Theme* theme;
        UIContext* context;
        Application* app;
        Server server;
        Client client;
        SharedPointer<TextBlock> status;
        SharedPointer<TextBlock> clientCount;

    public:
        MessengerWindow(Application& app);

        ~MessengerWindow();

        virtual void onUpdate(const uint64_t time) override;
    };
}