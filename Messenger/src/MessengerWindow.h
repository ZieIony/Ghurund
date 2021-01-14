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
        List<Server*> servers;
        List<Client*> clients;

    public:
        MessengerWindow(Application& app);

        ~MessengerWindow();
    };
}