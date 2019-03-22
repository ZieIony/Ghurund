#include "Renderer.h"

namespace Ghurund {
    const Ghurund::Type& Renderer::TYPE = Ghurund::Type([]() {return ghnew Renderer(); }, "Renderer");
  
    Status Renderer::init(Window & window, ResourceManager & resourceManager, ResourceContext & resourceContext) {
        this->graphics = &resourceContext.Graphics;
        this->parameterManager = &resourceContext.ParameterManager;

        swapChain = ghnew SwapChain();
        Status result = swapChain->init(resourceContext.Graphics, window, FRAME_COUNT);
        if(result!=Status::OK)
            return result;

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
        if(swapChain==nullptr)
            return;
        swapChain->uninitBuffers();
        delete swapChain;
        swapChain = nullptr;
    }

    void Renderer::render() {
        CommandList &commandList = startFrame();
        for(RenderStep *step:steps)
            step->draw(*graphics, commandList, stats);
        finishFrame();
    }
}