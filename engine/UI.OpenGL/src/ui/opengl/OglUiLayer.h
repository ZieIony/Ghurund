#pragma once

#include "engine/opengl/OpenGLDrawingContext.h"
#include "ui/UILayer.h"
#include "OglCanvas.h"

namespace Ghurund::UI::OpenGL {
    using namespace ::Ghurund::Engine::OpenGL;

    class OglUiLayer:public Ghurund::UI::UILayer<OpenGLDrawingContext> {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = OglUiLayer::GET_TYPE();
#pragma endregion

    private:
        IUIContext* context = nullptr;
        OglCanvas* canvas = nullptr;

    protected:
        virtual bool onSizeChanged() override {
            return true;
        }

    public:
        ~OglUiLayer() {
            uninit();
        }

        void init(Window& window);

        void uninit();

        inline IUIContext& getContext() {
            return *context;
        }

        __declspec(property(get = getContext)) IUIContext& Context;

        virtual void draw(OpenGLDrawingContext& context) override {}
    };
}