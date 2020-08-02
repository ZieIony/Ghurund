#pragma once

#include "Control.h"

namespace Ghurund {
    class ControlContainer : public Control {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ControlContainer);

        Control* child = nullptr;

    public:
        ~ControlContainer() {
            if (child) {
                child->Parent = nullptr;
                child->release();
            }
        }

        inline Control* getChild() {
            return child;
        }

        inline void setChild(Control* child) {
            if (this->child)
                this->child->Parent = nullptr;
            setPointer(this->child, child);
            if (this->child)
                this->child->Parent = this;
        }

        __declspec(property(get = getChild, put = setChild)) Control* Child;

        void measure() {
            Child->DesiredSize = DesiredSize;
            if (child)
                child->measure();

            if (desiredSize.x == LayoutSize::WRAP_CONTENT) {
                measuredSize.x = 0;
                if (child)
                    measuredSize.x = std::max(measuredSize.x, child->MeasuredSize.x);
            } else if (desiredSize.x == LayoutSize::MATCH_PARENT) {
                measuredSize.x = MAX_SIZE;
            } else {
                measuredSize.x = desiredSize.x;
            }

            if (desiredSize.y == LayoutSize::WRAP_CONTENT) {
                measuredSize.y = 0;
                if (child)
                    measuredSize.y = std::max(measuredSize.y, child->MeasuredSize.y);
            } else if (desiredSize.y == LayoutSize::MATCH_PARENT) {
                measuredSize.y = MAX_SIZE;
            } else {
                measuredSize.y = desiredSize.y;
            }
        }

        void layout(float x, float y, float width, float height) {
            __super::layout(x, y, width, height);
            if (child)
                child->layout(0, 0, width, height);
        }

        void draw(Canvas& canvas) {
            if (child) {
                auto& pos = child->Position;
                canvas.translate(pos.x, pos.y);
                child->draw(canvas);
                canvas.translate(-pos.x, -pos.y);
            }
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<ControlContainer>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(Control::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}