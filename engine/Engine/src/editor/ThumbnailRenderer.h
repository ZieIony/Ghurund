#pragma once

#include "entity/camera/Camera.h"
#include "graphics/Renderer.h"
#include "core/image/Image.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    class ThumbnailRenderer:public Object {
    private:
		Camera* camera = nullptr;
        Renderer* renderer = nullptr;
        Frame* frame = nullptr;
        RenderTarget* renderTarget = nullptr;
        DepthBuffer* depthBuffer = nullptr;

        ResourceContext* resourceContext = nullptr;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        ~ThumbnailRenderer() {
            if (camera)
                camera->release();
            delete renderer;
            delete frame;
        }

        void init(uint32_t width, uint32_t height);

        Status render(DrawableComponent& entity, Ghurund::Core::Image*& image);
        Status render(Mesh& mesh, Ghurund::Core::Image*& image);
        Status render(Material& material, Ghurund::Core::Image*& image);

        

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}