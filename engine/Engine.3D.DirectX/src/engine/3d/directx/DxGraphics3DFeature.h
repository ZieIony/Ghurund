#pragma once

#include "engine/3d/Graphics3DFeature.h"
#include "engine/directx/memory/DxGPUMemoryManager.h"

namespace Ghurund::Engine::_3D::DirectX {
    using namespace Ghurund::Engine::DirectX;

    class DxGraphics3DFeature: public Graphics3DFeature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DxGraphics3DFeature::GET_TYPE();
#pragma endregion

    private:
        DxGPUMemoryManager& memoryManager;
     
        void uninitDxGraphics3DFeature();

    protected:
        [[nodiscard]]
        virtual CoroutineTask<void> onInit() override;

        virtual void onUninit() override;

    public:
        DxGraphics3DFeature(
            ResourceManager& resourceManager,
            DxGPUMemoryManager& memoryManager
        ):Graphics3DFeature(resourceManager), memoryManager(memoryManager) {
        }

        virtual ~DxGraphics3DFeature() {
            if (IsInitialized)
                uninitDxGraphics3DFeature();
        }
    };
}
