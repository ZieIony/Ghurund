#pragma once

#include "DxGraphics.h"
#include "engine/directx/SwapChain.h"
#include "engine/graphics/Renderer.h"
#include "engine/directx/material/Material.h"
#include "Postprocess.h"
#include <core/Color.h>
#include <engine/parameter/ParameterManager.h>
#include "DxRenderingContext.h"

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
		//Model* fullScreenQuad = nullptr;
        Material* lightPassMaterial = nullptr;
        Postprocess* postprocess = nullptr;
        //RenderTarget* postprocessRenderTarget[FRAME_COUNT] = {};

        DxGraphics& graphics;
        ParameterManager& parameterManager;

    protected:
        virtual void onInit() override;

        virtual void onUninit() override;
        void uninitDxRenderer();

    public:
        DxRenderer(DxGraphics& graphics, ParameterManager& parameterManager):graphics(graphics), parameterManager(parameterManager) {}

        ~DxRenderer() {
            uninitDxRenderer();
        }

        virtual DxRenderingContext* makeRenderingContext(SystemWindow& window) override {
            return ghnew DxRenderingContext(window, graphics);
        }
    };
}