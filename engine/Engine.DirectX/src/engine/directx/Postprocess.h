#pragma once

#include "engine/directx/buffer/RenderTarget.h"
#include "engine/directx/material/DxMaterial.h"
#include "texture/Texture.h"

namespace Ghurund::Engine::DirectX {
    class Postprocess: public Resource {
    private:
        //Model* fullScreenQuad = nullptr;
        DxMaterial* material = nullptr;

    public:
        ~Postprocess() {
            //if (fullScreenQuad)
              //  fullScreenQuad->release();
            if (material)
                material->release();
        }

        void init(DxMaterial& material) {
            setPointer(this->material, &material);
            //fullScreenQuad = Models::makeQuad(resourceContext, *this->material);
        }

        virtual void invalidate() override {
            __super::invalidate();
        }

        virtual bool isValid() const override {
            return __super::isValid();
        }

        void process(Texture* texture, RenderTarget* renderTarget) {}
    };
}