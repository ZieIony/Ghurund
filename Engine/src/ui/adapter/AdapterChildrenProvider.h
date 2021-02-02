#pragma once

#include "ItemAdapter.h"
#include "ItemSource.h"
#include "AdapterChildrenProvider.h"

#include "ui/control/ChildrenProvider.h"

namespace Ghurund::UI {
    template<class ItemType, class ControlType>
    class AdapterChildrenProvider:public ChildrenProvider {
    private:
        ControlGroup& owner;
        ItemSource<ItemType>* items = nullptr;
        List<ItemAdapter<ItemType, ControlType>*> adapters;

        inline ItemAdapter<ItemType, ControlType>* findAdapter(size_t position) {
            for (auto a : adapters) {
                if (a->canHandleItem(items->get(position), position))
                    return a;
            }
            return nullptr;
        }

    public:
        AdapterChildrenProvider(ControlGroup& owner):owner(owner) {}

        ~AdapterChildrenProvider() {
            adapters.deleteItems();
            delete items;
        }

        virtual size_t getChildCount() const override {
            return items->Size;
        }

        virtual Control* getChild(size_t index) override {
            ItemAdapter<ItemType, ControlType>* adapter = findAdapter(index);
            ControlType* control = adapter->getControl();
            adapter->bind(*control, items->get(index), index);
            control->Parent = &owner;
            return control;
        }

        virtual void releaseChild(Control* control, size_t index) override {
            findAdapter(index)->recycleControl((ControlType*)control);
        }

        inline ItemSource<ItemType>* getItems() {
            return items;
        }

        inline void setItems(ItemSource<ItemType>* items) {
            this->items = items;
        }

        __declspec(property(get = getItems, put = setItems)) ItemSource<ItemType>* Items;

        inline List<ItemAdapter<ItemType, ControlType>*>& getAdapters() {
            return adapters;
        }

        inline void setAdapters(const List<ItemAdapter<ItemType, ControlType>*>& adapters) {
            this->adapters.clear();
            this->adapters.addAll(adapters);
        }

        __declspec(property(get = getAdapters, put = setAdapters)) List<ItemAdapter<ItemType, ControlType>*>& Adapters;

    };
}