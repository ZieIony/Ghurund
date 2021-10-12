#include "MessengerWindow.h"
#include "ui/UIFeature.h"
#include "net/Networking.h"

namespace Messenger {
    using namespace Ghurund;
    using namespace Ghurund::UI;
    using namespace Ghurund::Net;

    class MessengerApplication:public Application {
    private:
        Theme* lightTheme;

    public:
        MessengerApplication() {
            auto uiFeature = ghnew UIFeature(*this);
            Features.add<UIFeature>(uiFeature);
            Graphics2D& graphics2d = uiFeature->Graphics2D;
            lightTheme = ghnew LightTheme(*graphics2d.DWriteFactory, ResourceManager);
            LayoutLoader* layoutLoader = (LayoutLoader*)ResourceManager.Loaders.get<Layout>();
            layoutLoader->Theme = lightTheme;

            Features.add<Networking>(ghnew Networking());
        }

        ~MessengerApplication() {
            delete lightTheme;
        }

        virtual Status onInit() override {
            auto window = ghnew MessengerWindow(*this);
            window->Size = Settings.windowSize;
            Windows.add(window);
            window->Visible = true;
            window->activate();
            return Status::OK;
        }
    };
}
