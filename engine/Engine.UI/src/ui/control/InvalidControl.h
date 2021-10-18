#pragma once

#include "Control.h"
#include "ui/Color.h"
#include "ui/StrokeStyle.h"

namespace Ghurund::UI {
    class InvalidControl:public Control {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();
        Color backgroundColor = Color(1, 0, 0, 0.2f);
        Color borderColor = Color(1, 0, 0, 1.0f);
        StrokeStyle strokeStyle;

        virtual void onContextChanged() {
            __super::onContextChanged();
            strokeStyle.uninit();
            if (Context) {
                Array<float> dashes = { 3.0f, 4.0f };
                strokeStyle.init(Context->D2DFactory, dashes);
            }
        }

    public:
        InvalidControl() {
            MinSize = { 18, 18 };
            PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        }

        virtual void onDraw(Canvas& canvas) override;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };
}