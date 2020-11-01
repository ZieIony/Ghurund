#pragma once

#include "LayoutManager.h"
#include "ui/control/AdapterView.h"

namespace Ghurund::UI {
    template<class T, class ControlType>
    class HorizontalLayoutManager:public AdapterLayoutManager<T, ControlType> {
    private:
        unsigned int indexFirst = 0, indexLast = 0;
        float firstLeft = 0, firstRight = 0;
        float lastLeft = 0, lastRight = 0;

    public:
        virtual void scrollBy(AdapterView<T, ControlType>& adapterView, float dx, float dy) override {
            ItemSource<T>* items = adapterView.Items;
            scroll.x += dx;
            if (dx > 0) {
                addLeft(adapterView, adapterView.Size.width, adapterView.Size.height);
                scroll.x = std::min(scroll.x, 0.0f);
                removeLeft(adapterView);
            } else {
                addRight(adapterView, adapterView.Size.width, adapterView.Size.height);
                if (indexFirst + adapterView.Children.Size == items->Size)
                    scroll.y = std::max(scroll.y, -lastRight + adapterView.Size.height);
                removeTop(adapterView);
            }
        }

        void addLeft(AdapterView<T, ControlType>& adapterView, float parentWidth, float parentHeight) {
            while (firstLeft + scroll.x > 0 && indexFirst > 0) {
                indexFirst--;
                ControlType* control = adapterView.getChild(indexFirst);
                control->measure(parentWidth, parentHeight);
                control->layout(firstLeft - control->MeasuredSize.width, 0, control->MeasuredSize.width, adapterView.Size.height);
                adapterView.Children.insert(0, control);
                firstLeft = control->Position.x;
                firstRight = firstLeft + control->Size.width;
                control->release();
            }
        }

        void addRight(AdapterView<T, ControlType>& adapterView, float parentWidth, float parentHeight) {
            ItemSource<T>* items = adapterView.Items;
            while (lastRight + scroll.x < adapterView.Size.width && items->Size>indexLast) {
                ControlType* control = adapterView.getChild(indexLast);
                control->measure(parentWidth, parentHeight);
                control->layout(lastRight, 0, control->MeasuredSize.width, adapterView.Size.height);
                adapterView.Children.add(control);
                control->release();
                indexLast++;
                lastLeft = control->Position.x;
                lastRight = lastLeft + control->Size.width;
            }
        }

        void removeTop(AdapterView<T, ControlType>& adapterView) {
            while (adapterView.Children.Size > 0 && firstRight + scroll.x < 0) {
                adapterView.releaseChild(adapterView.Children[0], indexFirst);
                adapterView.Children.removeAt(0);
                if (adapterView.Children.Size > 0) {
                    Control* control = adapterView.Children[0];
                    firstLeft = control->Position.x;
                    firstRight = firstLeft + control->Size.width;
                }
                indexFirst++;
            }
        }

        void removeLeft(AdapterView<T, ControlType>& adapterView) {
            while (adapterView.Children.Size > 0 && lastLeft + scroll.x > adapterView.Size.width) {
                indexLast--;
                adapterView.releaseChild(adapterView.Children[adapterView.Children.Size - 1], indexLast);
                adapterView.Children.removeAt(adapterView.Children.Size - 1);
                if (adapterView.Children.Size > 0) {
                    Control* control = adapterView.Children[adapterView.Children.Size - 1];
                    lastLeft = control->Position.x;
                    lastRight = lastLeft + control->Size.width;
                }
            }
        }

        virtual const FloatSize measure(AdapterView<T, ControlType>& adapterView, float parentWidth, float parentHeight) {
            ItemSource<T>* items = adapterView.Items;
            if (!items) {
                Logger::log(LogType::WARNING, "AdapterView (with HorizontalLayoutManager) was not measured, because its item source is null\n");
                return { 0,0 };
            }
            if (adapterView.PreferredSize.width == PreferredSize::Width::FILL &&
                adapterView.PreferredSize.height == PreferredSize::Height::FILL)
                return { 0,0 };
            if ((float)adapterView.PreferredSize.width >= 0 &&
                (float)adapterView.PreferredSize.height >= 0) {
                return { (float)adapterView.PreferredSize.width, (float)adapterView.PreferredSize.height };
            }

            FloatSize measuredSize = { 0,0 };
            size_t i = indexFirst;
            while (i < items->getSize()) {
                ControlType* control = adapterView.getChild(i);
                control->measure(parentWidth, parentHeight);
                if (control->PreferredSize.width != PreferredSize::Width::FILL)
                    measuredSize.width += control->MeasuredSize.width;
                if (control->PreferredSize.height != PreferredSize::Height::FILL)
                    measuredSize.height = std::max(measuredSize.height, control->MeasuredSize.height);
                control->release();
                adapterView.releaseChild(control, i);
                i++;
            }

            return measuredSize;
        }

        virtual void layout(AdapterView<T, ControlType>& adapterView, float x, float y, float width, float height) {
            ItemSource<T>* items = adapterView.Items;
            if (!items)
                return;

            for (Control* c : adapterView.Children) {
                if (c->Size.height != height)
                    c->layout(c->Position.x, 0, c->Size.width, height);
            }

            addLeft(adapterView, width, height);
            addRight(adapterView, width, height);

            if (indexFirst + adapterView.Children.Size == items->Size)
                scroll.x = std::max(scroll.x, -lastRight + width);
            scroll.x = std::min(scroll.x, 0.0f);

            removeTop(adapterView);
            removeLeft(adapterView);
        }
    };

}