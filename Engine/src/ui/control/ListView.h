#pragma once

#include "ControlGroup.h"
#include "ItemAdapter.h"
#include "ui/layout/LayoutInflater.h"

namespace Ghurund::UI {
    template<class T>
    class ListView :public ControlGroup {
    private:
        template<class T2>
        class AdapterWithPool {
        public:
            ItemAdapter<T2>* adapter;
            PointerList<Control*> pool;

            AdapterWithPool(ItemAdapter<T2>* adapter):adapter(adapter) {}

            ~AdapterWithPool() {
                delete adapter;
            }

            Control* getControl() {
                if (pool.Empty)
                    return adapter->makeControl();
                Control* control = pool[pool.Size - 1];
                control->addReference();
                pool.removeAt(pool.Size - 1);
                return control;
            }

            void recycle(Control* c) {
                pool.add(c);
            }
        };

        inline static const char* CLASS_NAME = GH_STRINGIFY(ListView);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<ListView>();

        unsigned int indexTop = 0;
        float posTop = 0;
        List<AdapterWithPool<T>*> adapters;

        AdapterWithPool<T>* findAdapterForChild(const T& child) {
            for (AdapterWithPool<T>* a : adapters) {
                if (a->adapter->filter(child))
                    return a;
            }
            return nullptr;
        }

    public:
        ~ListView() {
            adapters.deleteItems();
        }

        float scroll = 0.0f;
        List<T> items;

        void addAdapter(ItemAdapter<T>* adapter) {
            adapters.add(ghnew AdapterWithPool<T>(adapter));
        }

        virtual void draw(Canvas& canvas) override {
            canvas.save();
            canvas.clipRect(position.x, position.y, size.x, size.y);
            canvas.translate(0, scroll);
            __super::draw(canvas);
            canvas.restore();
        }

        void layout(float x, float y, float width, float height) {
            Control::layout(x, y, width, height);
            layoutChildren();
        }

        void layoutChildren() {
            if (items.Empty)
                return;

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
        }

        virtual bool onMouseWheelEvent(const MouseWheelEventArgs& event) {
            if (items.Empty)
                return false;
            if (items.Size == Children.Size && Children[0]->Position.y == 0 && Children[Children.Size - 1]->Position.y <= Size.y)
                return false;

            if (event.Wheel == MouseWheel::VERTICAL) {
                scroll += event.Delta;
                layoutChildren();
                repaint();
            }
            return false;
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<ListView>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        inline static ListView* inflate(LayoutInflater& inflater, json& json) {
            ListView* listView = ghnew ListView();
            inflater.loadControl(listView, json);
            return listView;
        }
    };
}