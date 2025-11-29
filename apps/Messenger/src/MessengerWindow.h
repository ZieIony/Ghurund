#include "Common.h"
#include "core/application/Application.h"
#include "core/application/ApplicationWindow.h"
#include "core/math/MathUtils.h"
#include "core/window/SystemWindow.h"
#include "engine/net/Client.h"
#include "engine/net/Server.h"
#include "ui/directx/DxUIContext.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/theme/LightTheme.h"
#include <core/object/SharedPointer.h>
#include <engine/directx/DxRenderer.h>
#include <ui/text/TextBlock.h>
#include <ui/theme/Theme.h>

namespace Messenger {
    using namespace Ghurund::Engine::DirectX;
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;
    using namespace Ghurund::UI::DirectX;
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
        MessengerWindow(Ghurund::Core::Application& app);

        ~MessengerWindow();

        virtual void update(const uint64_t time) override;
    };
}