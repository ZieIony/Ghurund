module;

#include "net/Networking.h"
#include "graphics/Renderer.h"
#include "ui/style/LightTheme.h"
#include "core/application/Application.h"
#include "core/Int.h"

#include <format>

export module Messenger.MessengerApplication;

import Messenger.MessengerWindow;
import Ghurund.Engine.UI.UIFeature;

export namespace Messenger {
    using namespace Ghurund;
    using namespace Ghurund::UI;
    using namespace Ghurund::Net;

    class MessengerApplication:public Application {
    private:
        Theme* lightTheme;

    protected:
        Renderer renderer;
        ParameterManager parameterManager;

    public:
        MessengerApplication() {
            auto uiFeature = ghnew UIFeature(*this);
            Features.add(std::unique_ptr<UIFeature>(uiFeature));
            Ghurund::UI::Direct2D::Graphics2D& graphics2d = uiFeature->Graphics2D;
            lightTheme = ghnew LightTheme(ResourceManager);
            LayoutLoader* layoutLoader = (LayoutLoader*)ResourceManager.Loaders.get<Control>();
            layoutLoader->Theme = lightTheme;

            Features.add(std::make_unique<Graphics>());
            Features.add(std::make_unique<Networking>());
        }

        ~MessengerApplication() {
            delete lightTheme;
        }

        virtual void onInit() override {
            renderer.init(Features.get<Graphics>(), parameterManager);

            auto window = ghnew MessengerWindow(*this, renderer);
            window->Size = { Settings.get<uint32_t>("width"), Settings.get<uint32_t>("height") };
            Windows.add(window);
            window->Visible = true;
            window->bringToFront();
        }
    };
}
