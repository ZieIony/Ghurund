#pragma once

#include "Graphics.h"
#include "Materials.h"
#include "Postprocess.h"
#include "RenderStep.h"
#include "SwapChain.h"

#include "core/Object.h"
#include "game/entity/Model.h"
#include "game/entity/Models.h"
#include "game/entity/Scene.h"
#include "resource/ResourceManager.h"
#include "resource/ResourceContext.h"

namespace Ghurund {
    class Renderer: public Object {
    private:
        static const UINT FRAME_COUNT = 2;

        Model* fullScreenQuad = nullptr;
        Material* lightPassMaterial = nullptr;
        Postprocess* postprocess = nullptr;
        RenderTarget* postprocessRenderTarget[FRAME_COUNT] = {};

        SwapChain* swapChain = nullptr;
        Graphics* graphics = nullptr;
        ParameterManager* parameterManager = nullptr;
        Material* material = nullptr;
        Material* invalidMaterial = nullptr;
        RenderingStatistics stats;

        XMFLOAT4* clearColor = nullptr;

        List<RenderStep*> steps;

        CommandList& startFrame() {
            swapChain->startFrame(clearColor);

            CommandList& commandList = swapChain->CommandList;
            graphics->DescriptorAllocator.set(commandList.get());   // TODO: set allocator properly

            return commandList;
        }

        void finishFrame() {
            swapChain->finishFrame();
        }

    public:
        ~Renderer() {
            if (lightPassMaterial != nullptr)
                lightPassMaterial->release();
            if (invalidMaterial != nullptr)
                invalidMaterial->release();
            uninit();
            delete clearColor;
        }

        Status init(Window & window, ResourceManager & resourceManager, ResourceContext & resourceContext);

        void uninit();

        void render();

        void resize(unsigned int width, unsigned int height) {
            swapChain->resize(*graphics, width, height);
            //for(int i = 0; i<FRAME_COUNT; i++)
              //  postprocessRenderTarget[i]->resize(*graphics, width, height);
        }

        void setInvalidMaterial(Ghurund::Material * material) {
            setPointer(this->invalidMaterial, material);
        }

        __declspec(property(put = setInvalidMaterial)) Ghurund::Material * InvalidMaterial;

        XMFLOAT4 * getClearColor() {
            return clearColor;
        }

        void setClearColor(XMFLOAT4 * color) {
            delete clearColor;
            clearColor = color;
        }

        __declspec(property(get = getClearColor, put = setClearColor)) XMFLOAT4 * ClearColor;

        RenderingStatistics & getStatistics() {
            return stats;
        }

        __declspec(property(get = getStatistics)) RenderingStatistics & Statistics;

        List<RenderStep*> & getSteps() {
            return steps;
        }

        __declspec(property(get = getSteps)) List<RenderStep*> & Steps;
    };
}