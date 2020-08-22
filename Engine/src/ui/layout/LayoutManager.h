#pragma once

#include "ControlGroup.h"
#include "ItemAdapter.h"
#include "ui/layout/LayoutInflater.h"

namespace Ghurund::UI {
    class LayoutManager {
    public:
        virtual ~LayoutManager() = 0 {}

        virtual XMFLOAT2 scroll(float dx, float dy);
        virtual void measure() {}
        virtual void layout(float x, float y, float width, float height) = 0;
    };

    class VerticalLayoutManager :public LayoutManager {
    public:
        virtual void layout(float x, float y, float width, float height) {
            if (items.Empty)
                return;

            for (Control* c : Children) {
                if (c->Size.x != Size.x)
                    c->layout(0, c->Position.y, Size.x, c->Size.y);
            }
            if (Children.Size == 0) {
                T& item = items.get(0);
                AdapterWithPool<T>* adapter = findAdapterForChild(item);
                Control* control = adapter->getControl();
                adapter->adapter->bind(item, *control);
                control->measure();
                control->layout(0, posTop, Size.x, control->MeasuredSize.y);
                Children.add(control);
                control->release();
            }
            // add top
            while (Children[0]->Position.y + scroll > 0 && indexTop > 0) {
                indexTop--;
                T& item = items.get(indexTop);
                AdapterWithPool<T>* adapter = findAdapterForChild(item);
                Control* control = adapter->getControl();
                adapter->adapter->bind(item, *control);
                control->measure();
                control->layout(0, Children[0]->Position.y - control->MeasuredSize.y, Size.x, control->MeasuredSize.y);
                Children.insert(0, control);
                control->release();
            }
            //add bottom
            while (Children[Children.Size - 1]->Position.y + Children[Children.Size - 1]->Size.y + scroll < Size.y && items.Size>indexTop + Children.Size) {
                T& item = items.get(indexTop + Children.Size);
                AdapterWithPool<T>* adapter = findAdapterForChild(item);
                Control* control = adapter->getControl();
                adapter->adapter->bind(item, *control);
                control->measure();
                control->layout(0, Children[Children.Size - 1]->Position.y + Children[Children.Size - 1]->Size.y, Size.x, control->MeasuredSize.y);
                Children.add(control);
                control->release();
            }

            if (indexTop + Children.Size == items.Size)
                scroll = std::max(scroll, -Children[Children.Size - 1]->Position.y - Children[Children.Size - 1]->Size.y + Size.y);
            scroll = std::min(scroll, 0.0f);

            // remove top
            while (Children.Size > 0 && Children[0]->Position.y + Children[0]->Size.y + scroll < 0) {
                T& item = items.get(indexTop);
                AdapterWithPool<T>* adapter = findAdapterForChild(item);
                adapter->recycle(Children[0]);
                Children.removeAt(0);
                indexTop++;
            }
            // remove bottom
            while (Children.Size > 0 && Children[Children.Size - 1]->Position.y + scroll > Size.y) {
                T& item = items.get(indexTop + Children.Size - 1);
                AdapterWithPool<T>* adapter = findAdapterForChild(item);
                adapter->recycle(Children[Children.Size - 1]);
                Children.removeAt(Children.Size - 1);
            }
        }
    };

}