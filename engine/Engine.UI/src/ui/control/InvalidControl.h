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
        std::unique_ptr<IStrokeStyle> strokeStyle;

        virtual void onContextChanged() {
            __super::onContextChanged();
            if (Context) {
                Array<float> dashes = { 3.0f, 4.0f };
                strokeStyle.reset(Context->makeStrokeStyle(dashes));
            }
        }

    public:
        InvalidControl() {
            MinSize = { 18, 18 };
            PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::FILL };
        }

        virtual void onDraw(ICanvas& canvas) override;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}