#include "DemoWindow.h"

#include "core/application/Application.h"
#include "engine/directx/DxGraphicsFeatureFactory.h"
#include "engine/directx/DxRenderer.h"
#include "ui/directx/DxUIFeatureFactory.h"
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
        DemoWindow* window = nullptr;
        IntrusivePointer<CommandList> commandList;
        DxTextureFactory* textureFactory = nullptr;

        void uninitDemoApplication();

    protected:
        virtual void onInit() override;

        virtual void onUninit() override;

    public:
        DemoApplication() {
            Features.add<DxGraphicsFeature, DxGraphicsFeatureFactory>();
            Features.add<UIFeature, DxUIFeatureFactory>();
        }

        ~DemoApplication() {
            if (IsInitialized)
                uninitDemoApplication();
        }
    };
}
