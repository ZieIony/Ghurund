#pragma once

#include "MenuBarAdapter.h"
#include "MenuBarLayout.h"
#include "ui/Style.h"
#include "ui/widget/Widget.h"
#include "ui/layout/HorizontalLayoutManager.h"

namespace Ghurund::UI {
    class MenuBar: public Widget<MenuBar, MenuBarLayout> {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(MenuBar);
        
        List<MenuItem*> items;

    public:
        MenuBar(StyleWithLayout<MenuBar, MenuBarLayout>* style);

        ~MenuBar() {
            items.deleteItems();
        }

        inline List<MenuItem*>& getItems() {
            return items;
        }

        __declspec(property(get = getItems)) List<MenuItem*>& Items;

        inline static const Ghurund::Type& TYPE = TypeBuilder<MenuBar>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

    };

    typedef ScopedPointer<MenuBar> MenuBarPtr;
}