#include "core/application/Application.h"
#include "engine/graphics/Renderer.h"
#include "engine/net/Networking.h"
#include "MessengerWindow.h"
#include "ui/directx/DxUIFeature.h"
#include "ui/theme/LightTheme.h"
#include <engine/directx/DxRenderer.h>
#include <engine/parameter/ParameterManager.h>
#include <ui/directx/DxUIFeatureFactory.h>
#include "core/math/Int.h"

#include <cstdint>
#include <format>

namespace Messenger {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace Ghurund::UI;
    using namespace Ghurund::Net;

    class MessengerApplication:public Application {
    private:
        Theme* lightTheme;

    protected:
        DxRenderer* renderer;
        ParameterManager parameterManager;

    public:
        MessengerApplication() {
            auto drawableFactory = ghnew DrawableFactory(ResourceManager);
            Features.add<DxUIFeature, DxUIFeatureFactory>();
            lightTheme = ghnew LightTheme(ResourceManager, *drawableFactory);
            LayoutLoader* layoutLoader = (LayoutLoader*)ResourceManager.Loaders.get<Control>();
            //layoutLoader->Theme = lightTheme;
            renderer = ghnew DxRenderer(*Features.get<DxGraphics>());

            Features.add<DxGraphics>();
            Features.add<Networking>();
        }

        ~MessengerApplication() {
            delete lightTheme;
        }

        virtual void onInit() override {
            renderer->init();

            auto window = ghnew MessengerWindow(*this);
            window->Size = { parse<uint32_t>(Settings.get("width")), parse<uint32_t>(Settings.get("height")) };
            window->Visible = true;
            window->bringToFront();
        }
    };
}
