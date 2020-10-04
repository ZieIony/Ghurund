#pragma once

#include "ControlGroup.h"
#include "ui/Gravity.h"
#include "ui/layout/LinearLayoutManager.h"

namespace Ghurund::UI {
    class LinearLayout:public ControlGroup {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(LinearLayout);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<LinearLayout>();

        LinearLayoutManager layoutManager;

    public:
        inline Gravity& getGravity() {
            return layoutManager.gravity;
        }

        inline void setGravity(const Gravity& gravity) {
            layoutManager.gravity = gravity;
        }

        __declspec(property(get = getGravity, put = setGravity)) Gravity& Gravity;

        inline Orientation getOrientation() const {
            return layoutManager.orientation;
        }

        inline void setOrientation(Orientation orientation) {
            layoutManager.orientation = orientation;
        }

        __declspec(property(get = getOrientation, put = setOrientation)) Orientation Orientation;

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            measuredSize = layoutManager.measure(*this, parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            layoutManager.layout(*this, x, y, width, height);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<LinearLayout>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(ControlGroup::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<LinearLayout> LinearLayoutPtr;

    class HorizontalLayout:public LinearLayout {};

    typedef ScopedPointer<HorizontalLayout> HorizontalLayoutPtr;

    class VerticalLayout:public LinearLayout {
    public:
        VerticalLayout() {
            Orientation = Orientation::VERTICAL;
        }
    };
 
    typedef ScopedPointer<VerticalLayout> VerticalLayoutPtr;
}