#pragma once

#include "graphics/Renderer.h"
#include "ui/image/Image.h"

namespace Ghurund {
    class ThumbnailRenderer:public Object {
    private:
		Camera* camera = nullptr;
        Renderer* renderer = nullptr;
        Frame* frame = nullptr;
        RenderTarget* renderTarget = nullptr;
        DepthBuffer* depthBuffer = nullptr;

        ResourceContext* resourceContext = nullptr;

    protected:
        static const Ghurund::Type& GET_TYPE();

    public:
        ~ThumbnailRenderer() {
            if (camera)
                camera->release();
            delete renderer;
            delete frame;
        }

        void init(uint32_t width, uint32_t height);

        Status render(DrawableComponent& entity, Ghurund::UI::Image*& image);
        Status render(Mesh& mesh, Ghurund::UI::Image*& image);
        Status render(Material& material, Ghurund::UI::Image*& image);

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}