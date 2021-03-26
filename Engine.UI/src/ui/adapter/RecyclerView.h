#pragma once

#include "ItemAdapter.h"

#include "ui/control/ControlGroup.h"
#include "ui/layout/LayoutManager.h"

namespace Ghurund::UI {
    class RecyclerView:public ControlGroup {
    private:
        Event<Control> onScrolled = Event<Control>(*this);

    protected:
        LayoutManager* layoutManager = nullptr;

        static const Ghurund::Type& GET_TYPE();

    public:
        ChildrenProvider* childrenProvider;

        ~RecyclerView() {
            delete childrenProvider;
            delete layoutManager;
        }

        inline const FloatPoint& getScroll() const {
            return layoutManager->Scroll;
        }

        inline void setScroll(const FloatPoint& scroll) {
            setScroll(scroll.x, scroll.y);
        }

        inline void setScroll(float x, float y) {
            layoutManager->Scroll = { x, y };
        }

        __declspec(property(get = getScroll, put = setScroll)) const FloatPoint& Scroll;

        inline const FloatPoint& getMaxScroll() const {
            return layoutManager->MaxScroll;
        }

        __declspec(property(get = getMaxScroll)) const FloatPoint& MaxScroll;

        inline Event<Control>& getOnScrolled() {
            return onScrolled;
        }

        __declspec(property(get = getOnScrolled)) Event<Control>& OnScrolled;

        inline LayoutManager* getLayoutManager() {
            return layoutManager;
        }

        inline void setLayoutManager(LayoutManager* layoutManager) {
            this->layoutManager = layoutManager;
        }

        __declspec(property(get = getLayoutManager, put = setLayoutManager)) LayoutManager* LayoutManager;

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            if (layoutManager && childrenProvider)
                measuredSize = layoutManager->measure(*this, *childrenProvider, parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            if (layoutManager && childrenProvider)
                layoutManager->layout(*this, *childrenProvider, x, y, width, height);
        }

        virtual void onDraw(Canvas& canvas) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event);

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event);

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& args);

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}