#include "MessengerWindow.h"

#include "ui/control/Space.h"
#include "ui/widget/button/TextButton.h"
#include "ui/layout/LinearLayout.h"
#include "net/Networking.h"

namespace Messenger {
    using namespace Ghurund::Net;

    MessengerWindow::MessengerWindow(Application& app):OverlappedWindow(app.Timer) {
        this->app = &app;
        Ghurund::SwapChain* swapChain = ghnew Ghurund::SwapChain();
        swapChain->init(app.Graphics, &app.Graphics2D, *this);
        SwapChain = swapChain;

        const uint16_t port = 52109;

        theme = ghnew LightTheme(app.ResourceManager, app.ResourceContext, 0xff0078D7);
        context = ghnew UIContext(app.Graphics2D, *theme, *this);

        Ghurund::UI::Canvas* canvas = ghnew Ghurund::UI::Canvas();
        canvas->init(app.Graphics2D);
        SharedPointer<Ghurund::UI::RootView> rootView = ghnew Ghurund::UI::RootView(*context, *canvas);

        auto hostUDP = makeShared<TextButton>();
        hostUDP->Text = L"HOST";
        hostUDP->OnClicked.add([&app, this](Control&, const MouseClickedEventArgs& args) {
            Server* server = app.Networking.host(port);
            if (server)
                servers.add(server);
            return true;
        });
        auto connectUDP = makeShared<TextButton>();
        connectUDP->Text = L"CONNECT";
        connectUDP->OnClicked.add([&app, this](Control&, const MouseClickedEventArgs& args) {
            Client* client = app.Networking.connect(_T("localhost"), port);
            if (client)
                clients.add(client);
            return true;
        });
        auto sendUDP = makeShared<TextButton>();
        sendUDP->Text = L"SEND";
        sendUDP->OnClicked.add([](Control&, const MouseClickedEventArgs& args) {
            return true;
        });
        auto stopHosting = makeShared<TextButton>();
        stopHosting->Text = L"STOP HOSTING";
        stopHosting->OnClicked.add([this](Control&, const MouseClickedEventArgs& args) {
            servers.deleteItems();
            return true;
        });
        auto disconnect = makeShared<TextButton>();
        disconnect->Text = L"DISCONNECT";
        disconnect->OnClicked.add([this](Control&, const MouseClickedEventArgs& args) {
            clients.deleteItems();
            return true;
        });

        auto content = makeShared<VerticalLayout>();
        content->Children = {
            hostUDP, connectUDP, sendUDP,
            makeShared<Space>(),
            stopHosting, disconnect
        };
        rootView->Child = content;

        rootView->Theme = theme;
        rootView->BackgroundColor = theme->ColorBackground;
        RootView = rootView;
    }

    MessengerWindow::~MessengerWindow() {
        delete context;
        delete theme;
        servers.deleteItems();
        clients.deleteItems();
    }
}
