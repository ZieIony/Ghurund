#pragma once

#include "ui/Alignment.h"
#include "ui/Orientation.h"
#include "ui/layout/FlowLayoutManager.h"

namespace Ghurund::UI {
    class FlowLayout:public ControlGroup {
    private:
        Alignment alignment;
        Orientation orientation = Orientation::HORIZONTAL;
        FlowLayoutManager layoutManager;
        ListChildrenProvider childrenProvider = ListChildrenProvider(*this);

        /*void relayoutLine(List<Control*>& currentLine) {
            if (currentLine.Size < 2)
                return;

            int maxY = Integer.MIN_VALUE, minY = currentLine.get(0)->getTop();
            for (Control* control : currentLine) {
                maxY = Math.max(maxY, control->getBottom());
            }
            for (Control* control : currentLine) {
                if ((params.alignment & Alignment.TOP) == Alignment.TOP) {
                    control->layout(control->getLeft(), minY, control->getRight(), minY + control->Size.height);
                } else if ((params.alignment & Alignment.BOTTOM) == Alignment.BOTTOM) {
                    control->layout(control->getLeft(), maxY - control->Size.height, control->getRight(), maxY);
                } else if ((params.alignment & Alignment.CENTER_VERTICAL) == Alignment.CENTER_VERTICAL) {
                    int top = std::max((maxY + minY) / 2 - control->Size.height / 2, minY);
                    int bottom = top + control->Size.height;
                    control->layout(control->getLeft(), top, control->getRight(), bottom);
                }
            }
        }*/

    protected:
        static const Ghurund::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = NoArgsConstructor<FlowLayout>();
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(FlowLayout))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        inline bool getReverseLayout() const {
            return layoutManager.reverseLayout;
        }

        inline void setReverseLayout(bool reverseLayout) {
            layoutManager.reverseLayout = reverseLayout;
        }

        __declspec(property(get = getReverseLayout, put = setReverseLayout)) bool ReverseLayout;

        inline Spacing& getSpacing() {
            return layoutManager.spacing;
        }

        inline void setSpacing(const Spacing& spacing) {
            layoutManager.spacing = spacing;
        }

        __declspec(property(get = getSpacing, put = setSpacing)) Spacing& Spacing;

        inline Alignment& getAlignment() {
            return alignment;
        }

        inline void setAlignment(const Alignment& alignment) {
            this->alignment = alignment;
        }

        __declspec(property(get = getAlignment, put = setAlignment)) Alignment& Alignment;

        inline Orientation getOrientation() const {
            return orientation;
        }

        inline void setOrientation(Orientation orientation) {
            this->orientation = orientation;
        }

        __declspec(property(get = getOrientation, put = setOrientation)) Orientation Orientation;

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            measuredSize = layoutManager.measure(*this, childrenProvider, parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            layoutManager.layout(*this, childrenProvider, x, y, width, height);
        }

        bool dispatchMouseMotionEvent(const Ghurund::Input::MouseMotionEventArgs& event) {
            return __super::dispatchMouseMotionEvent(event);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}