#pragma once

#include "Control.h"
#include "ui/Color.h"
#include "ui/StrokeStyle.h"

namespace Ghurund::UI {
    class InvalidControl:public Control {
    protected:
        Color backgroundColor = Color(1, 0, 0, 0.2f);
        Color borderColor = Color(1, 0, 0, 1.0f);
        std::unique_ptr<IStrokeStyle> strokeStyle;

        virtual void onContextChanged() {
            __super::onContextChanged();
            if (Context) {
                Array<float> dashes = { 3.0f, 4.0f };
                strokeStyle.reset(Context->makeStrokeStyle(dashes));
            }
        }

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        InvalidControl() {
            //MinSize = { 18, 18 };
        }

        virtual void onDraw(ICanvas& canvas) override;
    };
}