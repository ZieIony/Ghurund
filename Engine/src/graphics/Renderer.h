#pragma once

#include "Graphics.h"
#include "SwapChain.h"
#include "game/Scene.h"

namespace Ghurund {
    class Renderer {
    private:
        static const UINT FRAME_COUNT = 2;
  
        SwapChain *swapChain;

    public:
        Status init(Graphics &graphics, Window &window) {
            swapChain = ghnew SwapChain();
            Status result = swapChain->init(graphics, window, FRAME_COUNT);
            if(result!=Status::OK)
                return result;

            return Status::OK;
        }

        shared_ptr<CommandList> startFrame() {
            swapChain->startFrame();

            return swapChain->getCommandList();
        }

        void finishFrame(){
            swapChain->finishFrame();
        }

        Status uninit() {
            delete swapChain;
            swapChain = nullptr;

            return Status::OK;
        }
    };
}