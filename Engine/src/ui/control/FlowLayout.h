#pragma once

#include "ui/layout/FlowLayoutManager.h"
#include "ui/Gravity.h"
#include "ui/Orientation.h"

namespace Ghurund::UI {
    class FlowLayout:public ControlGroup {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(FlowLayout);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<FlowLayout>();

        Gravity gravity;
        Orientation orientation = Orientation::HORIZONTAL;
        FlowLayoutManager layoutManager;

        /*void relayoutLine(List<Control*>& currentLine) {
            if (currentLine.Size < 2)
                return;

            int maxY = Integer.MIN_VALUE, minY = currentLine.get(0)->getTop();
            for (Control* control : currentLine) {
                maxY = Math.max(maxY, control->getBottom());
            }
            for (Control* control : currentLine) {
                if ((params.gravity & Gravity.TOP) == Gravity.TOP) {
                    control->layout(control->getLeft(), minY, control->getRight(), minY + control->Size.height);
                } else if ((params.gravity & Gravity.BOTTOM) == Gravity.BOTTOM) {
                    control->layout(control->getLeft(), maxY - control->Size.height, control->getRight(), maxY);
                } else if ((params.gravity & Gravity.CENTER_VERTICAL) == Gravity.CENTER_VERTICAL) {
                    int top = std::max((maxY + minY) / 2 - control->Size.height / 2, minY);
                    int bottom = top + control->Size.height;
                    control->layout(control->getLeft(), top, control->getRight(), bottom);
                }
            }
        }*/

    public:
        inline bool getReverseLayout() const {
            return layoutManager.reverseLayout;
        }

        inline void setReverseLayout(bool reverseLayout) {
            layoutManager.reverseLayout = reverseLayout;
        }

        __declspec(property(get = getReverseLayout, put = setReverseLayout)) bool ReverseLayout;

        inline float getHorizontalSpacing() const {
            return layoutManager.horizontalSpacing;
        }

        inline void setHorizontalSpacing(float horizontalSpacing) {
            layoutManager.horizontalSpacing = horizontalSpacing;
        }

        __declspec(property(get = getHorizontalSpacing, put = setHorizontalSpacing)) float HorizontalSpacing;

        inline float getVerticalSpacing() const {
            return layoutManager.verticalSpacing;
        }

        inline void setVerticalSpacing(float verticalSpacing) {
            layoutManager.verticalSpacing = verticalSpacing;
        }

        __declspec(property(get = getVerticalSpacing, put = setVerticalSpacing)) float VerticalSpacing;

        inline Gravity& getGravity() {
            return gravity;
        }

        inline void setGravity(const Gravity& gravity) {
            this->gravity = gravity;
        }

        __declspec(property(get = getGravity, put = setGravity)) Gravity& Gravity;

        inline Orientation getOrientation() const {
            return orientation;
        }

        inline void setOrientation(Orientation orientation) {
            this->orientation = orientation;
        }

        __declspec(property(get = getOrientation, put = setOrientation)) Orientation Orientation;

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            measuredSize = layoutManager.measure(*this, parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            layoutManager.layout(*this, x, y, width, height);
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<FlowLayout>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(ControlGroup::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<FlowLayout> FlowLayoutPtr;
}