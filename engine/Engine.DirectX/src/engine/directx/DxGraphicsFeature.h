#pragma once

#include "DxGraphics.h"

#include "core/feature/Feature.h"
#include "core/reflection/Type.h"
#include "engine/graphics/GraphicsFeature.h"
#include "resource/DxGraphicsResourceFactory.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class DxGraphicsFeature: public GraphicsFeature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DxGraphicsFeature::GET_TYPE();
#pragma endregion

    private:
        class DxGraphics* graphics = nullptr;
        class DxGraphicsCommandList* commandList = nullptr;
        class DxGPUMemoryManager* memoryManager = nullptr;
        class DxShaderCompiler* shaderCompiler = nullptr;
        class DxGraphicsResourceFactory* resourceFactory = nullptr;
        class DxRenderer* renderer = nullptr;

        void uninitGraphicsFeature();

    protected:
        virtual IGraphicsResourceFactory& getResourceFactoryInternal() override {
            return *resourceFactory;
        }

        [[nodiscard]]
        virtual CoroutineTask<void> onInit() override;

        virtual void onUninit() override;

    public:
        DxGraphicsFeature(ResourceManager& resourceManager):GraphicsFeature(resourceManager) {}

        ~DxGraphicsFeature() {
            if (IsInitialized)
                uninitGraphicsFeature();
        }

        inline DxGraphics& getGraphics() {
            return *graphics;
        }

        __declspec(property(get = getGraphics)) DxGraphics& Graphics;

        inline DxRenderer& getRenderer() {
            return *renderer;
        }

        __declspec(property(get = getRenderer)) DxRenderer& Renderer;

        inline DxGPUMemoryManager& getMemoryManager() {
            return *memoryManager;
        }

        __declspec(property(get = getMemoryManager)) DxGPUMemoryManager& MemoryManager;
    };
}
