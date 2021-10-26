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
        ChildrenProvider* childrenProvider = nullptr;

        static const Ghurund::Core::Type& GET_TYPE();

    public:
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

        inline void setLayoutManager(std::unique_ptr<LayoutManager> layoutManager) {
            delete this->layoutManager;
            this->layoutManager = layoutManager.release();
            if (this->LayoutManager && childrenProvider)
                this->layoutManager->setGroup(*this, *childrenProvider);
        }

        __declspec(property(get = getLayoutManager, put = setLayoutManager)) LayoutManager* LayoutManager;

        inline ChildrenProvider* getChildrenProvider() {
            return childrenProvider;
        }

        inline void setChildrenProvider(std::unique_ptr<ChildrenProvider> childrenProvider) {
            delete this->childrenProvider;
            this->childrenProvider = childrenProvider.release();
            if (LayoutManager && this->childrenProvider)
                layoutManager->setGroup(*this, *this->childrenProvider);
        }

        __declspec(property(get = getChildrenProvider, put = setChildrenProvider)) ChildrenProvider* ChildrenProvider;

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            if (layoutManager && childrenProvider)
                measuredSize = layoutManager->measure(parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            if (layoutManager && childrenProvider)
                layoutManager->layout(x, y, width, height);
        }

        virtual void onDraw(ICanvas& canvas) override;

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event);

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event);

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& args);

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };
}