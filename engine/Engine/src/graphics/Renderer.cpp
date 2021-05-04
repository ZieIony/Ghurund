#include "ghpch.h"
#include "Renderer.h"

namespace Ghurund {
    const Ghurund::Type& Renderer::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<Renderer>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Renderer))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    Status Renderer::init(Graphics& graphics, ParameterManager& parameterManager) {
        this->graphics = &graphics;
        this->parameterManager = &parameterManager;

        /*for(int i = 0; i<FRAME_COUNT; i++) {
            postprocessRenderTarget[i] = ghnew RenderTarget();
            postprocessRenderTarget[i]->init(*graphics, window.Width, window.Height, DXGI_FORMAT_B8G8R8A8_UNORM);
        }*/

        //lightPassMaterial = Materials::makeLightPass(resourceManager, resourceContext);
        //fullScreenQuad = Models::makeQuad(resourceContext, *lightPassMaterial);

        return Status::OK;
    }

    void Renderer::uninit() {
        /*for(int i = 0; i<FRAME_COUNT; i++) {
            delete postprocessRenderTarget[i];
            postprocessRenderTarget[i] = nullptr;
        }*/
    }

}