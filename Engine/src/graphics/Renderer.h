#pragma once

#include "Graphics.h"
#include "SwapChain.h"
#include "core/Object.h"
#include "game/entity/Scene.h"
#include "RenderingBatch.h"

namespace Ghurund {
    class Renderer: public Object {
    private:
        static const UINT FRAME_COUNT = 2;
  
        SwapChain *swapChain;
        Graphics *graphics = nullptr;
        Material *material = nullptr;

    public:
        Renderer() {
            swapChain = ghnew SwapChain();
        }

        ~Renderer() {
            uninit();
            delete swapChain;
            swapChain = nullptr;
        }

        Status init(Graphics &graphics, Window &window) {
            this->graphics = &graphics;
            Status result = swapChain->init(graphics, window, FRAME_COUNT);
            if(result!=Status::OK)
                return result;

            return Status::OK;
        }

        void uninit() {
            if(swapChain==nullptr)
                return;
            swapChain->uninitBuffers();
        }

        CommandList &startFrame() {
            swapChain->startFrame();
            
            CommandList &commandList = swapChain->CommandList;
            graphics->DescriptorAllocator.set(commandList.get());   // TODO: set allocator properly

            return commandList;
        }

        void draw(Camera &camera, Entity &entity, ParameterManager &parameterManager) {
            RenderingBatch batch;
            batch.initParameters(parameterManager);
            XMFLOAT4X4 identity;
            XMStoreFloat4x4(&identity, XMMatrixIdentity());
            entity.flatten(batch, identity);
            batch.cull(camera);
            //onPreDraw(batch);
            CommandList &commandList = swapChain->CommandList;
            batch.draw(commandList, parameterManager, material);
            batch.clear();
        }

        void finishFrame(){
            swapChain->finishFrame();
        }

        void resize(unsigned int width, unsigned int height) {
            swapChain->resize(*graphics, width, height);
        }

        void setMaterial(Material *material) {
            setPointer(this->material, material);
        }

        __declspec(property(put = setMaterial)) Material *Material;
    };
}