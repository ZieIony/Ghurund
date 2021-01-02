#pragma once

#include "ItemAdapter.h"
#include "ItemSource.h"
#include "AdapterChildrenProvider.h"

#include "ui/control/ControlGroup.h"
#include "ui/layout/LayoutManager.h"

namespace Ghurund::UI {
    template<class T, IsControl ControlType>
    class RecyclerView:public ControlGroup {
    private:
        static inline const auto& CONSTRUCTOR = NoArgsConstructor<RecyclerView<T, ControlType>>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(RecyclerView))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        Event<Control> onScrolled = Event<Control>(*this);

    protected:
        ItemSource<T>* items = nullptr;
        LayoutManager* layoutManager = nullptr;
        List<ItemAdapter<T, ControlType>*> adapters;
        AdapterChildrenProvider<T, ControlType> childrenProvider = AdapterChildrenProvider(*this);

    public:
        ~RecyclerView() {
            adapters.deleteItems();
            delete items;
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

        inline ItemSource<T>* getItems() {
            return items;
        }

        inline void setItems(ItemSource<T>* items) {
            this->items = items;
        }

        __declspec(property(get = getItems, put = setItems)) ItemSource<T>* Items;

        inline LayoutManager* getLayoutManager() {
            return layoutManager;
        }

        inline void setLayoutManager(LayoutManager* layoutManager) {
            this->layoutManager = layoutManager;
        }

        __declspec(property(get = getLayoutManager, put = setLayoutManager)) LayoutManager* LayoutManager;

        inline List<ItemAdapter<T, ControlType>*>& getAdapters() {
            return adapters;
        }

        inline void setAdapters(const List<ItemAdapter<T, ControlType>*>& adapters) {
            this->adapters.clear();
            this->adapters.addAll(adapters);
        }

        __declspec(property(get = getAdapters, put = setAdapters)) List<ItemAdapter<T, ControlType>*>& Adapters;

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            if (layoutManager)
                measuredSize = layoutManager->measure(*this, childrenProvider, parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            if (layoutManager)
                layoutManager->layout(*this, childrenProvider, x, y, width, height);
        }

        virtual void onDraw(Canvas& canvas) override {
            if (!layoutManager || !items)
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
            if (layoutManager) {
                if (args.Wheel == MouseWheel::VERTICAL) {
                    layoutManager->scrollBy(*this, childrenProvider, 0, (float)args.Delta);
                    onScrolled();
                    repaint();
                } else {
                    layoutManager->scrollBy(*this, childrenProvider, (float)args.Delta, 0);
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