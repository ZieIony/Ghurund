#pragma once

#include "engine/2d/directx/DxGraphics2DFeature.h"
#include "engine/2d/directx/DxGraphics2DFeatureFactory.h"
#include "engine/application/GameApplication.h"
#include "engine/directx/DxGraphicsFeature.h"
#include "engine/directx/DxGraphicsFeatureFactory.h"
#include "engine/directx/rendering/DxRenderer.h"
#include "ui/directx/DxUIFeature.h"
#include "ui/directx/DxUIFeatureFactory.h"

namespace Sample {
    using namespace Ghurund::Engine;
    using namespace Ghurund::Engine::DirectX;
    using namespace Ghurund::Engine::_2D;
    using namespace Ghurund::Engine::_2D::DirectX;
    using namespace Ghurund::Core;
    using namespace Ghurund::UI;
    using namespace Ghurund::UI::DirectX;

    class SampleApplication:public GameApplication {
    private:
        class SampleWindow* window = nullptr;

        void uninitDemoApplication();

    protected:
        virtual void onInit() override;

        virtual void onUninit() override;

    public:
        SampleApplication() {
            Features.add<DxGraphicsFeature, DxGraphicsFeatureFactory>();
            Features.add<DxGraphics2DFeature, DxGraphics2DFeatureFactory>();
            Features.add<DxUIFeature, DxUIFeatureFactory>();
        }

        ~SampleApplication() {
			if (IsInitialized)
                uninitDemoApplication();
        }
    };
}
