#include "core/application/Application.h"
#include "DemoWindow.h"
#include "engine/directx/DxRenderer.h"
#include "engine/parameter/ParameterManager.h"
#include "ui/directx/DxUIFeature.h"
#include "ui/directx/UIFeatureFactory.h"
#include "ui/loading/DrawableFactory.h"
#include "ui/theme/LightTheme.h"

namespace Demo {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace Ghurund::Core;
    using namespace Ghurund::UI::DirectX;

    class DemoApplication:public Application {
    private:
        DxRenderer* renderer = nullptr;
        LightTheme* theme = nullptr;
        Ghurund::UI::DrawableFactory* drawableFactory = nullptr;
        DemoWindow* window = nullptr;

        void uninitDemoApplication();

    protected:
        virtual void onInit() override;

        virtual void onUninit() override;

    public:
        DemoApplication() {
            Features.add<DxGraphics>();
            Features.add<UIFeature, UIFeatureFactory>();
        }

        ~DemoApplication() {
            if (IsInitialized)
                uninitDemoApplication();
        }
    };
}
