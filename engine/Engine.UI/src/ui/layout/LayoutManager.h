#pragma once

#include "ui/control/ChildrenProvider.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
    class LayoutManager {
    protected:
        FloatPoint scroll = { 0,0 };
        FloatPoint maxScroll = { 0.0f, 0.0f };
        ControlGroup* group = nullptr;
        ChildrenProvider* provider = nullptr;

        float measureMaxWidth();

        float measureMaxHeight();

    public:
        virtual ~LayoutManager() = 0 {}

        void setGroup(ControlGroup& group, ChildrenProvider& provider) {
            this->group = &group;
            this->provider = &provider;
            scroll = { 0, 0 };
            maxScroll = { 0, 0 };
        }

        inline const FloatPoint& getScroll() const {
            return scroll;
        }

        inline void setScroll(const FloatPoint& scroll) {
            this->scroll = scroll;
        }

        __declspec(property(get = getScroll, put = setScroll)) const FloatPoint& Scroll;

        virtual void scrollBy(float dx, float dy) {}

        inline const FloatPoint& getMaxScroll() const {
            return maxScroll;
        }

        __declspec(property(get = getMaxScroll)) const FloatPoint& MaxScroll;

        virtual bool focusNext() {
            return group->focusNext();
        }

        virtual bool focusPrevious() {
            return group->focusPrevious();
        }

        virtual bool focusUp() {
            return group->focusUp();
        }

        virtual bool focusDown() {
            return group->focusDown();
        }

        virtual bool focusLeft() {
            return group->focusLeft();
        }

        virtual bool focusRight() {
            return group->focusRight();
        }

        virtual const Ghurund::Core::FloatSize measure(float parentWidth, float parentHeight) {
            for (Control* c : group->Children) {
                if (!c->Visible)
                    continue;
                c->measure(parentWidth, parentHeight);
            }
            return { 0,0 };
        }

        virtual void layout(float x, float y, float width, float height) = 0;
    };
}