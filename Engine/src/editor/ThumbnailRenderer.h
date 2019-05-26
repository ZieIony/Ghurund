#pragma once

#include "graphics/Renderer.h"
#include "graphics/texture/Image.h"

namespace Ghurund {
    class ThumbnailRenderer:public Object {
    private:
        Camera* camera = nullptr;
        Renderer* renderer = nullptr;
        Frame* frame = nullptr;
        RenderTarget* renderTarget = nullptr;
        DepthBuffer* depthBuffer = nullptr;
        RenderStep* step = nullptr;

        ResourceManager* resourceManager = nullptr;
        ResourceContext* resourceContext = nullptr;

    public:
        ~ThumbnailRenderer() {
            if (camera)
                camera->release();
            delete renderer;
            delete frame;
            delete step;
        }

        void init(ResourceManager& resourceManager, ResourceContext& context, UINT32 width, UINT32 height);

        Status render(Entity& entity, Image*& image);
        Status render(Mesh& mesh, Image*& image);
        Status render(Material& material, Image*& image);

        const static Ghurund::Type& TYPE;
     
        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}