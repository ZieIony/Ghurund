#pragma once

#include "engine/directx/buffer/RenderTarget.h"
#include "Material.h"
#include "texture/Texture.h"

namespace Ghurund::Engine::DirectX {
    class Postprocess: public Resource {
    private:
        //Model* fullScreenQuad = nullptr;
        Material* material = nullptr;

    protected:
        virtual void loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) override {
            throw NotImplementedException();
        }

        virtual void saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const override {
            throw NotImplementedException();
        }

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

        void process(Texture* texture, RenderTarget* renderTarget) {}
    };
}