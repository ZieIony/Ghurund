#include "Renderer.h"

namespace Ghurund {
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

    void Renderer::draw(Camera &camera, Entity & entity, ParameterManager & parameterManager, Material *overrideMaterial, Material *invalidMaterial) {
        RenderStep *step = ghnew RenderStep();
        step->Camera = &camera;
        XMFLOAT4X4 identity;
        XMStoreFloat4x4(&identity, XMMatrixIdentity());
        entity.flatten(*step, identity);

        steps.add(step);
    }

    void Renderer::render() {
        CommandList &commandList = startFrame();
        for(RenderStep *step:steps)
            step->draw(*graphics, commandList, *parameterManager, stats);
        finishFrame();
        steps.deleteItems();
    }
}