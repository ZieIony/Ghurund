module;

#include "Common.h"
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
#include "ui/direct2d/UIContext.h"

export module Messenger.MessengerWindow;

import Ghurund.Engine.Application.ApplicationWindow;
import Ghurund.Engine.UI.UILayer;
import Ghurund.Engine.UI.UIFeature;

export namespace Messenger {
    using namespace Ghurund;
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;
    using namespace Ghurund::UI::Direct2D;
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
        MessengerWindow(Ghurund::Core::Application& app, Renderer& renderer);

        ~MessengerWindow();

        virtual void update(const uint64_t time) override;
    };
}