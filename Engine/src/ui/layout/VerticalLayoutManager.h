#pragma once

#include "LayoutManager.h"
#include "ui/control/AdapterView.h"

namespace Ghurund::UI {
    template<class T, class ControlType>
    class VerticalLayoutManager:public AdapterLayoutManager<T, ControlType> {
    private:
        unsigned int indexTop = 0, indexBottom = 0;
        float firstTop = 0, firstBottom = 0;
        float lastTop = 0, lastBottom = 0;

    public:
        virtual void scrollBy(AdapterView<T, ControlType>& adapterView, float dx, float dy) override {
            ItemSource<T>* items = adapterView.Items;
            scroll.y += dy;
            if (dy > 0) {
                addTop(adapterView);
                scroll.y = std::min(scroll.y, 0.0f);
                removeBottom(adapterView);
            } else {
                addBottom(adapterView);
                if (indexTop + adapterView.Children.Size == items->Size)
                    scroll.y = std::max(scroll.y, -lastBottom + adapterView.Size.height);
                removeTop(adapterView);
            }
        }

        void addTop(AdapterView<T, ControlType>& adapterView) {
            while (firstTop + scroll.y > 0 && indexTop > 0) {
                indexTop--;
                Control* control = adapterView.getChild(indexTop);
                control->layout(0, firstTop - control->MeasuredSize.height, adapterView.Size.width, control->MeasuredSize.height);
                adapterView.Children.insert(0, control);
                firstTop = control->Position.y;
                firstBottom = firstTop + control->Size.height;
                control->release();
            }
        }

        void addBottom(AdapterView<T, ControlType>& adapterView) {
            ItemSource<T>* items = adapterView.Items;
            while (lastBottom + scroll.y < adapterView.Size.height && items->Size>indexBottom) {
                Control* control = adapterView.getChild(indexBottom);
                control->layout(0, lastBottom, adapterView.Size.width, control->MeasuredSize.height);
                adapterView.Children.add(control);
                control->release();
                indexBottom++;
                lastTop = control->Position.y;
                lastBottom = lastTop + control->Size.height;
            }
        }

        void removeTop(AdapterView<T, ControlType>& adapterView) {
            while (adapterView.Children.Size > 0 && firstBottom + scroll.y < 0) {
                adapterView.releaseChild(adapterView.Children[0], indexTop);
                adapterView.Children.removeAt(0);
                if (adapterView.Children.Size > 0) {
                    Control* control = adapterView.Children[0];
                    firstTop = control->Position.y;
                    firstBottom = firstTop + control->Size.height;
                }
                indexTop++;
            }
        }

        void removeBottom(AdapterView<T, ControlType>& adapterView) {
            while (adapterView.Children.Size > 0 && lastTop + scroll.y > adapterView.Size.height) {
                indexBottom--;
                adapterView.releaseChild(adapterView.Children[adapterView.Children.Size - 1], indexBottom);
                adapterView.Children.removeAt(adapterView.Children.Size - 1);
                if (adapterView.Children.Size > 0) {
                    Control* control = adapterView.Children[adapterView.Children.Size - 1];
                    lastTop = control->Position.y;
                    lastBottom = lastTop + control->Size.height;
                }
            }
        }

        virtual const FloatSize measure(AdapterView<T, ControlType>& adapterView) {
            if (adapterView.PreferredSize.width == PreferredSize::Width::FILL && adapterView.PreferredSize.height == PreferredSize::Height::FILL)
                return { 0,0 };
            if (adapterView.PreferredSize.width >= 0 && adapterView.PreferredSize.height >= 0)
                return { adapterView.PreferredSize.width,adapterView.PreferredSize.height };

            float width = 0;
            float height = 0;
            ItemSource<T>* items = adapterView.Items;
            for (size_t i = 0; i < items->Size; i++) {
                Control* control = adapterView.getChild(i);
                control->measure(100, 100); // TODO: pass parent size
                if (control->PreferredSize.width != PreferredSize::Width::FILL)
                    width = std::max(width, control->MeasuredSize.width);
                if (control->PreferredSize.height != PreferredSize::Height::FILL)
                    height += control->MeasuredSize.height;
                adapterView.releaseChild(control, i);
            }

            if (adapterView.PreferredSize.width >= 0)
                width = adapterView.PreferredSize.width;
            if (adapterView.PreferredSize.height >= 0)
                height = adapterView.PreferredSize.height;
            return { width, height };
        }

        virtual void layout(AdapterView<T, ControlType>& adapterView, float x, float y, float width, float height) {
            ItemSource<T>* items = adapterView.Items;
            if (!items)
                return;

            for (Control* c : adapterView.Children) {
                if (c->Size.width != width)
                    c->layout(0, c->Position.y, width, c->Size.height);
            }

            addTop(adapterView);
            addBottom(adapterView);

            if (indexTop + adapterView.Children.Size == items->Size)
                scroll.y = std::max(scroll.y, -lastBottom + height);
            scroll.y = std::min(scroll.y, 0.0f);

            removeTop(adapterView);
            removeBottom(adapterView);
        }
    };

}