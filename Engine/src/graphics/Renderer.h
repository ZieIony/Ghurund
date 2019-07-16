#pragma once

#include "Graphics.h"
#include "Materials.h"
#include "Postprocess.h"
#include "SwapChain.h"

#include "core/Object.h"
#include "graphics/entity/Scene.h"
#include "resource/ResourceManager.h"
#include "resource/ResourceContext.h"

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

    public:
        ~Renderer() {
            if (lightPassMaterial != nullptr)
                lightPassMaterial->release();
            uninit();
            delete clearColor;
        }

        Status init(ResourceContext& resourceContext);

        void uninit();

		CommandList& startFrame(Frame& frame) {
			frame.start(clearColor);

			CommandList& commandList = frame.CommandList;
			graphics->DescriptorAllocator.set(commandList.get());   // TODO: set allocator properly
			stats.startFrame();

			return commandList;
		}

		void finishFrame(Frame& frame) {
			stats.finishFrame();
			frame.finish();
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

        const static Ghurund::Type& TYPE;

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}