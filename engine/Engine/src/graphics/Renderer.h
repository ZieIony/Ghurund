#pragma once

#include "Graphics.h"
#include "Materials.h"
#include "Postprocess.h"
#include "SwapChain.h"

#include "core/Object.h"
#include "graphics/entity/Scene.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund {
    class Renderer: public Object {
    private:
		//Model* fullScreenQuad = nullptr;
        Material* lightPassMaterial = nullptr;
        Postprocess* postprocess = nullptr;
        //RenderTarget* postprocessRenderTarget[FRAME_COUNT] = {};

        Graphics* graphics = nullptr;
        ParameterManager* parameterManager = nullptr;
        RenderingStatistics stats;

        XMFLOAT4* clearColor = nullptr;

    protected:
        static const Ghurund::Type& GET_TYPE();

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

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}