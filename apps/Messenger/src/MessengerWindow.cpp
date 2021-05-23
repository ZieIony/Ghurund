#include "MessengerWindow.h"
#include "TextMessage.h"
#include "core/window/WindowClass.h"

#include "ui/control/Space.h"
#include "ui/layout/LinearLayout.h"
#include "net/Networking.h"

#include <ranges>
#include "ui/UIFeature.h"

namespace Messenger {
    using namespace Ghurund::Net;
    using namespace std::ranges;

    MessengerWindow::MessengerWindow(Ghurund::Application& app):ApplicationWindow(WindowClass::WINDOWED, app) {
        /*UIFeature* uiFeature = app.Features.get<UIFeature>();
        Graphics2D& graphics2d = uiFeature->Graphics2D;
        const uint16_t port = 52109;

        theme = ghnew LightTheme(app.ResourceManager, app.ResourceContext, 0xff0078D7);
        context = ghnew UIContext(graphics2d, *theme, *this);

        Ghurund::UI::Canvas* canvas = ghnew Ghurund::UI::Canvas();
        canvas->init(graphics2d);
        SharedPointer<Ghurund::UI::RootView> rootView = ghnew Ghurund::UI::RootView(*context, *canvas);

        status = makeShared<TextBlock>();
        clientCount = makeShared<TextBlock>();

        auto hostUDP = makeShared<TextButton>(ghnew TextButtonFlatLayout());
        hostUDP->Text = L"HOST";
        hostUDP->OnClicked.add([&app, this](Control&, const MouseClickedEventArgs& args) {
            if (server.host(port) == Status::OK) {
                server.OnNewClientConnection.add([](Server& server, const Connection& connection) {
                    return true;
                });
                server.OnConnected.add([this](Server& server, const Connection& connection) {
                    status->Text = L"Hosting";
                    status->invalidate();
                    return true;
                });
                server.OnDisconnected.add([this](Server& server, const ClientDisconnection& disconnection) {
                    status->Text = L"Disconnected";
                    status->invalidate();
                    return true;
                });
            }
            return true;
        });
        auto connectUDP = makeShared<TextButton>(ghnew TextButtonFlatLayout());
        connectUDP->Text = L"CONNECT";
        connectUDP->OnClicked.add([&app, this](Control&, const MouseClickedEventArgs& args) {
            if (client.connect(_T("localhost"), port) == Status::OK) {
                client.OnConnected.add([this](Client& server) {
                    status->Text = L"Connected";
                    status->invalidate();
                    return true;
                });
                client.OnDisconnected.add([this](Client& client, const DisconnectionReason& disconnection) {
                    status->Text = L"Disconnected";
                    status->invalidate();
                    return true;
                });
            }
            return true;
        });
        auto sendUDP = makeShared<TextButton>(ghnew TextButtonFlatLayout());
        sendUDP->Text = L"SEND TO CLIENTS";
        sendUDP->OnClicked.add([this](Control&, const MouseClickedEventArgs& args) {
            TextMessage* message = ghnew TextMessage();
            client.send(message);
            return true;
        });
        auto sendUDP2 = makeShared<TextButton>(ghnew TextButtonFlatLayout());
        sendUDP->Text = L"SEND TO SERVER";
        sendUDP->OnClicked.add([](Control&, const MouseClickedEventArgs& args) {
            return true;
        });
        auto stopHosting = makeShared<TextButton>(ghnew TextButtonFlatLayout());
        stopHosting->Text = L"STOP HOSTING";
        stopHosting->OnClicked.add([this](Control&, const MouseClickedEventArgs& args) {
            server.shutdown();
            return true;
        });
        auto disconnect = makeShared<TextButton>(ghnew TextButtonFlatLayout());
        disconnect->Text = L"DISCONNECT";
        disconnect->OnClicked.add([this](Control&, const MouseClickedEventArgs& args) {
            client.disconnect();
            return true;
        });

        auto content = makeShared<VerticalLayout>();
        content->Children = {
            hostUDP, stopHosting, sendUDP,
            makeShared<Space>(),
            connectUDP, disconnect, sendUDP2,
            makeShared<Space>(),
            status, clientCount
        };
        rootView->Child = content;

        rootView->Theme = theme;
        rootView->BackgroundColor = theme->ColorBackground;
        RootView = rootView;*/
    }

    MessengerWindow::~MessengerWindow() {
        delete context;
        context = nullptr;
        delete theme;
    }

    void MessengerWindow::update(const uint64_t time) {
        /*if (server.Hosting) {
            server.update(time);
            clientCount->Text = fmt::format(L"server: {} client(s)", server.Connections.count([](Connection* c) {
                return c->Connected;
            })).c_str();
        } else {
            client.update(time);
            clientCount->Text = fmt::format(L"client: {}", client.Connected).c_str();
        }
        clientCount->invalidate();*/
        __super::update(time);
    }
}
