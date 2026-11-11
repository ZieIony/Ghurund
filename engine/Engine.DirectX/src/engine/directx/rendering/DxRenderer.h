#pragma once

#include "DxRenderingContext.h"

#include "engine/directx/DxGraphics.h"
#include "engine/graphics/rendering/Renderer.h"

namespace Ghurund::Engine::DirectX {
    using namespace ::DirectX;
    using namespace Ghurund::Core;

    class DxRenderer: public Renderer {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DxRenderer::GET_TYPE();
#pragma endregion

    private:
        DxGraphics& graphics;
        DxGPUMemoryManager& memoryManager;

    protected:
        virtual void onInit() override;

        virtual void onDeinit() override;
        void uninitDxRenderer();

    public:
        DxRenderer(DxGraphics& graphics, DxGPUMemoryManager& memoryManager):graphics(graphics), memoryManager(memoryManager) {}

        ~DxRenderer() {
            uninitDxRenderer();
        }

        virtual DxRenderingContext* makeRenderingContext(SystemWindow& window) override {
            return ghnew DxRenderingContext(window, graphics, memoryManager);
        }
    };
}
