#pragma once

#include "MenuBarItemAdapter.h"
#include "ui/adapter/AdapterLayout.h"
#include "ui/layout/HorizontalLayoutManager.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class MenuBar: public Widget {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = MenuBar::GET_TYPE();
#pragma endregion

    private:
        AdapterLayout* adapterLayout = nullptr;
        MenuBarItemAdapter* itemAdapter;
        List<MenuItem*> items;

    protected:
        void onLayoutChanged() {
            __super::onLayoutChanged();
            Control* layoutControl = layout.get();
            if (layoutControl) {
                setPointer(adapterLayout, (Ghurund::UI::AdapterLayout*)layoutControl->find("adapterLayout"));
                if (adapterLayout) {
                    //adapterLayout->ItemAdapter = std::make_unique<MenuBarItemAdapter>();
                    //adapterLayout->LayoutManager = std::make_unique<HorizontalLayoutManager>();
                }
            }
        }

        void update() {
            auto adapter = itemAdapter;
            adapterLayout->ItemAdapter = std::unique_ptr<MenuBarItemAdapter>(adapter);
            //itemAdapter->Items = items;
        }

    public:
        ~MenuBar() {
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