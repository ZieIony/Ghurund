#pragma once

#include "engine/directx/buffer/RenderTarget.h"
#include "texture/DxTexture.h"

namespace Ghurund::Engine::DirectX {
    class Postprocess: public Resource {
    private:
        //Model* fullScreenQuad = nullptr;
        Material* material = nullptr;

    public:
        ~Postprocess() {
            //if (fullScreenQuad)
              //  fullScreenQuad->release();
            if (material)
                material->release();
        }

        void init(Material& material) {
            setPointer(this->material, &material);
            //fullScreenQuad = Models::makeQuad(resourceContext, *this->material);
        }

        virtual void invalidate() override {
            __super::invalidate();
        }

        virtual bool isValid() const override {
            return __super::isValid();
        }

        void process(DxTexture* texture, RenderTarget* renderTarget) {}
    };
}