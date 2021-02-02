#pragma once

#include "ItemAdapter.h"

#include "ui/control/ControlGroup.h"
#include "ui/layout/LayoutManager.h"

namespace Ghurund::UI {
    class RecyclerView:public ControlGroup {
    private:
        static inline const auto& CONSTRUCTOR = NoArgsConstructor<RecyclerView>();

        Event<Control> onScrolled = Event<Control>(*this);

    protected:
        LayoutManager* layoutManager = nullptr;

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(RecyclerView))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        ChildrenProvider* childrenProvider;

        ~RecyclerView() {
            delete childrenProvider;
            delete layoutManager;
        }

        inline const XMFLOAT2& getScroll() const {
            return layoutManager->Scroll;
        }

        inline void setScroll(const XMFLOAT2& scroll) {
            setScroll(scroll.x, scroll.y);
        }

        inline void setScroll(float x, float y) {
            layoutManager->Scroll = { x,y };
        }

        __declspec(property(get = getScroll, put = setScroll)) const XMFLOAT2& Scroll;

        inline const XMFLOAT2& getMaxScroll() const {
            return layoutManager->MaxScroll;
        }

        __declspec(property(get = getMaxScroll)) const XMFLOAT2& MaxScroll;

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

        virtual void onDraw(Canvas& canvas) override {
            if (!layoutManager)
                return;

            canvas.save();
            canvas.clipRect(0, 0, Size.width, Size.height);
            auto& scroll = layoutManager->Scroll;
            canvas.translate(scroll.x, scroll.y);
            for (Control* c : Children)
                c->draw(canvas);
            canvas.restoreClipRect();
            canvas.restore();
        }

        virtual bool dispatchMouseButtonEvent(const MouseButtonEventArgs& event) {
            if (!layoutManager)
                return false;

            const XMFLOAT2& scroll = layoutManager->Scroll;
            return __super::dispatchMouseButtonEvent(event.translate(-scroll.x, -scroll.y, event.Inside));
        }

        virtual bool dispatchMouseMotionEvent(const MouseMotionEventArgs& event) {
            if (!layoutManager)
                return false;

            const XMFLOAT2& scroll = layoutManager->Scroll;
            return __super::dispatchMouseMotionEvent(event.translate(-scroll.x, -scroll.y, event.Inside));
        }

        virtual bool dispatchMouseWheelEvent(const MouseWheelEventArgs& args) {
            if (layoutManager && childrenProvider) {
                if (args.Wheel == MouseWheel::VERTICAL) {
                    layoutManager->scrollBy(*this, *childrenProvider, 0, (float)args.Delta);
                    onScrolled();
                    repaint();
                } else {
                    layoutManager->scrollBy(*this, *childrenProvider, (float)args.Delta, 0);
                    onScrolled();
                    repaint();
                }
            }

            return OnMouseWheel(args);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}