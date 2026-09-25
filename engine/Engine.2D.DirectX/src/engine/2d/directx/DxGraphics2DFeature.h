#pragma once

#include "engine/2d/Graphics2DFeature.h"
#include "engine/directx/memory/DxGPUMemoryManager.h"

namespace Ghurund::Engine::_2D::DirectX {
    using namespace Ghurund::Engine::DirectX;

    class DxGraphics2DFeature: public Graphics2DFeature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DxGraphics2DFeature::GET_TYPE();
#pragma endregion

    private:
        DxGPUMemoryManager& memoryManager;

        void uninitDxGraphicsFeature();

    protected:
        [[nodiscard]]
        virtual CoroutineTask<void> onInit() override;

        virtual void onUninit() override;

    public:
        DxGraphics2DFeature(
            ResourceManager& resourceManager,
            DxGPUMemoryManager& memoryManager
        ):Graphics2DFeature(resourceManager), memoryManager(memoryManager) {}

        ~DxGraphics2DFeature() {
            if (IsInitialized)
                uninitDxGraphicsFeature();
        }
    };
}
