#pragma once

#include "ItemAdapter.h"

#include "ui/control/ChildrenProvider.h"

namespace Ghurund::UI {
    template<class T = void*, IsControl ControlType = Control>
    class RecyclerView;

    template<class ItemType, class ControlType>
    class AdapterChildrenProvider:public ChildrenProvider {
    private:
        RecyclerView<ItemType, ControlType>& owner;

        inline ItemAdapter<ItemType, ControlType>* findAdapter(size_t position) {
            for (auto a : owner.Adapters) {
                if (a->canHandleItem(owner.Items->get(position), position))
                    return a;
            }
            return nullptr;
        }

    public:
        AdapterChildrenProvider(RecyclerView<ItemType, ControlType>& owner):owner(owner) {}

        virtual size_t getChildCount() const override {
            return owner.Items->Size;
        }

        virtual Control* getChild(size_t index) override {
            ItemAdapter<ItemType, ControlType>* adapter = findAdapter(index);
            ControlType* control = adapter->getControl();
            adapter->bind(*control, owner.Items->get(index), index);
            return control;
        }

        virtual void releaseChild(Control* control, size_t index) override {
            findAdapter(index)->recycleControl((ControlType*)control);
        }
    };
}