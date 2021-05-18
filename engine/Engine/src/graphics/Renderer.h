#pragma once

#include "Graphics.h"
#include "Materials.h"
#include "Postprocess.h"
#include "SwapChain.h"

#include "core/Object.h"
#include "graphics/entity/Scene.h"
#include "core/resource/ResourceManager.h"

#include "reflection_46d71a27_5bac_4460_86a7_87a3a5b8fa83.h"

namespace Ghurund {
    class Renderer: public Object {
        reflection_46d71a27_5bac_4460_86a7_87a3a5b8fa83

    private:
		//Model* fullScreenQuad = nullptr;
        Material* lightPassMaterial = nullptr;
        Postprocess* postprocess = nullptr;
        //RenderTarget* postprocessRenderTarget[FRAME_COUNT] = {};

        Graphics* graphics = nullptr;
        ParameterManager* parameterManager = nullptr;
        RenderingStatistics stats;

        XMFLOAT4* clearColor = nullptr;

    public:
        ~Renderer() {
            if (lightPassMaterial != nullptr)
                lightPassMaterial->release();
            uninit();
            delete clearColor;
        }

        Status init(Graphics& graphics, ParameterManager& parameterManager);

        void uninit();

		CommandList& startFrame(Frame& frame) {
			frame.start(clearColor);

			CommandList& commandList = frame.CommandList;
			graphics->DescriptorAllocator.set(commandList.get());   // TODO: set allocator properly
			stats.startFrame();

			return commandList;
		}

		Status finishFrame(Frame& frame) {
			stats.finishFrame();
			return frame.finish();
		}

        const XMFLOAT4* getClearColor() const {
            return clearColor;
        }

        void setClearColor(const XMFLOAT4* color) {
            delete clearColor;
            clearColor = ghnew XMFLOAT4(*color);
        }

        __declspec(property(get = getClearColor, put = setClearColor)) const XMFLOAT4* ClearColor;

        RenderingStatistics& getStatistics() {
            return stats;
        }

        __declspec(property(get = getStatistics)) RenderingStatistics& Statistics;
    };
}