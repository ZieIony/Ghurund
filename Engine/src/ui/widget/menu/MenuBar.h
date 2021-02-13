#pragma once

#include "MenuBarAdapter.h"
#include "MenuBarLayout.h"
#include "ui/style/Style.h"
#include "ui/widget/Widget.h"
#include "ui/layout/HorizontalLayoutManager.h"

namespace Ghurund::UI {
    class MenuBar: public Widget<MenuBarLayout> {
    private:
        ButtonMenuBarAdapter* adapter;
        List<MenuItem*> items;

    protected:
        virtual void onLayoutChanged() override;

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(MenuBar))
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        MenuBar(LayoutLoader& loader);

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

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

    };

    typedef SharedPointer<MenuBar> MenuBarPtr;
}