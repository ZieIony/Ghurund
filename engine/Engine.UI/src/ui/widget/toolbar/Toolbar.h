#pragma once

#include "ToolbarItemAdapter.h"
#include "ui/adapter/AdapterLayout.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class Toolbar: public Widget {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Toolbar::GET_TYPE();
#pragma endregion

    private:
        AdapterLayout* adapterLayout = nullptr;
        ToolbarItemAdapter* itemAdapter;
        List<MenuItem*> items;

    protected:
        void onLayoutChanged();

    public:
        ~Toolbar() {
            items.deleteItems();
        }

        inline List<MenuItem*>& getItems() {
            return items;
        }

        inline void setItems(const List<MenuItem*>& items) {
            this->items.clear();
            this->items.addAll(items);
        }

        __declspec(property(get = getItems, put = setItems)) List<MenuItem*>& Items;
    };
}