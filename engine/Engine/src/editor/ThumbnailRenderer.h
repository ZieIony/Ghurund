#pragma once

#include "graphics/Renderer.h"
#include "core/image/Image.h"

#include "entity/camera/Camera.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    class ThumbnailRenderer:public Object {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ThumbnailRenderer::GET_TYPE();
#pragma endregion

    private:
		Camera* camera = nullptr;
        Renderer* renderer = nullptr;
        Frame* frame = nullptr;
        RenderTarget* renderTarget = nullptr;
        DepthBuffer* depthBuffer = nullptr;


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
    };
}