#pragma once

#include "Graphics.h"
#include "SwapChain.h"
#include "core/Object.h"
#include "game/entity/Scene.h"
#include "RenderingBatch.h"
#include "Materials.h"
#include "resource/ResourceManager.h"

namespace Ghurund {
    class Renderer: public Object {
    private:
        static const UINT FRAME_COUNT = 2;

        SwapChain *swapChain;
        Graphics *graphics = nullptr;
        Material *material = nullptr;
#if defined(_DEBUG) || defined(GHURUND_EDITOR)
        Material *invalidMaterial = nullptr;
#endif

    public:
        Renderer() {
            swapChain = ghnew SwapChain();
        }

        ~Renderer() {
            invalidMaterial->release();
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
            batch.draw(commandList, parameterManager, material
#if defined(_DEBUG) || defined(GHURUND_EDITOR)
                       , invalidMaterial
#endif
            );
            batch.clear();
        }

        void finishFrame() {
            swapChain->finishFrame();
        }

        void resize(unsigned int width, unsigned int height) {
            swapChain->resize(*graphics, width, height);
        }

        void setMaterial(Material *material) {
            setPointer(this->material, material);
        }

        __declspec(property(put = setMaterial)) Material *Material;

#if defined(_DEBUG) || defined(GHURUND_EDITOR)
        void setInvalidMaterial(Ghurund::Material *material) {
            setPointer(this->invalidMaterial, material);
        }

        __declspec(property(put = setInvalidMaterial)) Ghurund::Material *InvalidMaterial;
#endif
    };
}