#pragma once

#include "DxGraphics.h"

#include "core/reflection/Type.h"
#include "core/feature/Feature.h"
#include "shader/compiler/DxShaderCompiler.h"
#include "texture/DxTextureLoader.h"
#include "mesh/DxMeshLoader.h"
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
        DxGraphics graphics;
        IntrusivePointer<CommandList> commandList;
        DxGPUMemoryManager* memoryManager = nullptr;
        SharedPointer<DxShaderCompiler> shaderCompiler;
        IntrusivePointer<DxMeshLoader> meshLoader;
        DxGraphicsResourceFactory* resourceFactory = nullptr;

        void uninitGraphicsFeature();

    protected:
        virtual IGraphicsResourceFactory& getResourceFactoryInternal() override {
            return *resourceFactory;
        }

    public:
        DxGraphicsFeature(ResourceManager& resourceManager):GraphicsFeature(resourceManager) {}

        ~DxGraphicsFeature() {
            if (IsInitialized)
                uninitGraphicsFeature();
        }

        [[nodiscard]]
        virtual CoroutineTask<void> onInit() override;

        virtual void onUninit() override;

        inline DxGraphics& getGraphics() {
            return graphics;
        }

        __declspec(property(get = getGraphics)) DxGraphics& Graphics;

        inline DxGPUMemoryManager& getMemoryManager() {
            return *memoryManager;
        }

        __declspec(property(get = getMemoryManager)) DxGPUMemoryManager& MemoryManager;
    };
}
