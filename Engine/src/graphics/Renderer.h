#pragma once

#include "Graphics.h"
#include "SwapChain.h"
#include "game/Scene.h"

namespace Ghurund {
    class Renderer {
    private:
        static const UINT FRAME_COUNT = 2;
  
        SwapChain *swapChain;
        Graphics *graphics;

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
            
            CommandList &commandList = swapChain->getCommandList();
            graphics->DescriptorAllocator.set(commandList.get());   // TODO: set allocator properly

            return commandList;
        }

        void finishFrame(){
            swapChain->finishFrame();
        }

        void resize(unsigned int width, unsigned int height) {
            swapChain->resize(*graphics, width, height);
        }
    };
}