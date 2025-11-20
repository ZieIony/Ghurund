#pragma once

#include "ui/UILayer.h"

namespace Ghurund::UI::OpenGL {
    class OglUiLayer:public Ghurund::UI::UILayer {
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
    };
}