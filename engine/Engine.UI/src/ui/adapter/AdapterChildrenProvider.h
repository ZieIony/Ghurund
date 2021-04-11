#pragma once

#include "ItemAdapter.h"
#include "ItemSource.h"
#include "AdapterChildrenProvider.h"

#include "core/Concepts.h"
#include "ui/control/ChildrenProvider.h"

namespace Ghurund::UI {
    template<class ItemType, class ControlType, Derived<ItemSource<ItemType>> ItemSourceType = ListItemSource<ItemType>>
    class AdapterChildrenProvider:public ChildrenProvider {
    private:
        ItemSourceType items;

    protected:
        virtual ItemAdapter<ItemType, ControlType>& getAdapter(size_t position) = 0;

    public:
        virtual size_t getChildCount() const override {
            return items.Size;
        }

        virtual Control* getChild(size_t index) override {
            ItemAdapter<ItemType, ControlType>& adapter = getAdapter(index);
            ControlType* control = adapter.getControl();
            adapter.bind(*control, items.get(index), index);
            //control->Parent = &owner;
            return control;
        }

        virtual void releaseChild(Control* control, size_t index) override {
            getAdapter(index).recycleControl((ControlType*)control);
        }

        inline ItemSourceType& getItemSource() {
            return items;
        }

        __declspec(property(get = getItemSource)) ItemSourceType& ItemSource;
    };

    template<typename ItemType, typename ControlType, Derived<ItemAdapter<ItemType, ControlType>> AdapterType>
    class SingleAdapterChildrenProvider:public AdapterChildrenProvider<ItemType, ControlType> {
    private:
        AdapterType adapter;

    protected:
        virtual ItemAdapter<ItemType, ControlType>& getAdapter(size_t position) override {
            return adapter;
        }
    };
}