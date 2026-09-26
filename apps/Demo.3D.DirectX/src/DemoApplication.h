#pragma once

#include "engine/3d/directx/DxGraphics3DFeature.h"
#include "engine/3d/directx/DxGraphics3DFeatureFactory.h"
#include "engine/application/GameApplication.h"
#include "engine/directx/DxGraphicsFeature.h"
#include "engine/directx/DxGraphicsFeatureFactory.h"
#include "engine/directx/DxRenderer.h"
#include "ui/directx/DxUIFeature.h"
#include "ui/directx/DxUIFeatureFactory.h"

namespace Demo {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace Ghurund::Engine::_3D::DirectX;
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;
    using namespace Ghurund::UI::DirectX;

    class DemoWindow;

    class DemoApplication:public GameApplication {
    private:
        DxRenderer* renderer = nullptr;
        DemoWindow* window = nullptr;

        void uninitDemoApplication();

    protected:
        virtual void onInit() override;

        virtual void onUninit() override;

    public:
        DemoApplication() {
            Features.add<DxGraphics3DFeature, DxGraphics3DFeatureFactory>();
            Features.add<DxGraphicsFeature, DxGraphicsFeatureFactory>();
            Features.add<DxUIFeature, DxUIFeatureFactory>();
        }

        ~DemoApplication() {
			if (IsInitialized)
                uninitDemoApplication();
        }
    };
}
