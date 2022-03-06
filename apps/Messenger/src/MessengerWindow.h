#pragma once

#include "Common.h"
#include "application/ApplicationWindow.h"
#include "core/application/Application.h"
#include "core/window/SystemWindow.h"
#include "core/math/MathUtils.h"
#include "ui/layout/StackLayout.h"
#include "ui/control/PaddingContainer.h"
#include "ui/RootView.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/style/LightTheme.h"
#include "net/Server.h"
#include "net/Client.h"

namespace Messenger {
    using namespace Ghurund;
    using namespace Ghurund::UI;
    using namespace Ghurund::Net;

    class MessengerWindow:public ApplicationWindow {
    private:
        Theme* theme;
        UIContext* context;
        Server server;
        Client client;
        SharedPointer<TextBlock> status;
        SharedPointer<TextBlock> clientCount;

    public:
        MessengerWindow(Ghurund::Application& app, Renderer& renderer);

        ~MessengerWindow();

        virtual void update(const uint64_t time) override;
    };
}