#pragma once

#include "DxGraphics.h"

#include "core/reflection/Type.h"
#include "core/feature/Feature.h"
#include "shader/compiler/DxShaderCompiler.h"
#include "texture/DxTextureFactory.h"

namespace Ghurund::Engine::DirectX {
    using namespace Ghurund::Core;

    class DxGraphicsFeature: public Ghurund::Core::Feature {
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
        DxGPUMemoryManager* memoryManager;
        ResourceManager& resourceManager;
        SharedPointer<DxShaderCompiler> shaderCompiler;
        SharedPointer<DxTextureFactory> textureFactory;

        void uninitGraphicsFeature();

    public:
        DxGraphicsFeature(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        ~DxGraphicsFeature() {
            if (IsInitialized)
                uninitGraphicsFeature();
        }

        virtual void onInit() override;

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