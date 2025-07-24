#pragma once

#include "engine/directx/Graphics.h"
#include "engine/directx/SwapChain.h"
#include "Postprocess.h"

#include "core/object/Object.h"
#include "graphics/RenderingStatistics.h"
#include "Material.h"
#include <parameter/ParameterManager.h>
#include <core/Color.h>

namespace Ghurund::Engine::DirectX {
    using namespace ::DirectX;
    using namespace Ghurund::Core;

    class Renderer: public Object {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Renderer::GET_TYPE();
#pragma endregion

    private:
		//Model* fullScreenQuad = nullptr;
        Material* lightPassMaterial = nullptr;
        Postprocess* postprocess = nullptr;
        //RenderTarget* postprocessRenderTarget[FRAME_COUNT] = {};

        // borrowed
        Graphics* graphics = nullptr;
        // borrowed
        ParameterManager* parameterManager = nullptr;
        RenderingStatistics stats;

    public:
        ~Renderer() {
            if (lightPassMaterial != nullptr)
                lightPassMaterial->release();
            uninit();
        }

        void init(NotNull<Graphics> graphics, NotNull<ParameterManager> parameterManager);

        void uninit();

		CommandList& startFrame(Frame& frame) {
			frame.start();

			CommandList& commandList = frame.CommandList;
			graphics->DescriptorAllocator.set(commandList.get());   // TODO: set allocator properly
			stats.startFrame();

			return commandList;
		}

        void clear(Frame& frame, const Color* clearColor) {
            frame.clear(clearColor);
        }

		void finishFrame(Frame& frame) {
			stats.finishFrame();
			frame.finish();
		}

        RenderingStatistics& getStatistics() {
            return stats;
        }

        __declspec(property(get = getStatistics)) RenderingStatistics& Statistics;
    };
}