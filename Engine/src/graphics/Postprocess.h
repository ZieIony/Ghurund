#pragma once

#include "buffer/RenderTarget.h"
#include "game/entity/Models.h"

namespace Ghurund {
    class Postprocess: public Resource {
    private:
        Model* fullScreenQuad = nullptr;
        Material* material = nullptr;

    protected:
        virtual Status loadInternal(ResourceManager& resourceManager, ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) override {
            return Status::NOT_IMPLEMENTED;
        }

        virtual Status saveInternal(ResourceManager& resourceManager, ResourceContext &context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const override {
            return Status::NOT_IMPLEMENTED;
        }

    public:
        ~Postprocess() {
            if (fullScreenQuad)
                fullScreenQuad->release();
            if (material)
                material->release();
        }

        void init(ResourceContext & resourceContext, Material & material) {
            setPointer(this->material, &material);
            fullScreenQuad = Models::makeQuad(resourceContext, *this->material);
        }

        void process(Texture * texture, RenderTarget * renderTarget) {}
    };
}