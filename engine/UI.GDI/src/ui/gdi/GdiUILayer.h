#pragma once

#include "core/application/Layer.h"
#include "UIContext.h"
#include "ui/RootView.h"
#include "ui/UILayer.h"
#include "GdiCanvas.h"
#include "GdiDrawingContext.h"

namespace Ghurund::UI::GDI {
    class GdiUiLayer:public Ghurund::UI::UILayer<GdiDrawingContext> {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = GdiUiLayer::GET_TYPE();
#pragma endregion

    private:
        GdiCanvas* canvas;
        IUIContext* context;

    public:
        ~GdiUiLayer() {
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