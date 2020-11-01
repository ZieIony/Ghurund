#pragma once

#include "ToolbarAdapter.h"
#include "ToolbarLayout.h"
#include "ui/Style.h"
#include "ui/control/ColorView.h"
#include "ui/layout/LinearLayout.h"
#include "ui/control/AdapterView.h"
#include "ui/layout/HorizontalLayoutManager.h"

namespace Ghurund::UI {
    class Toolbar: public Widget<Toolbar, ToolbarLayout> {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Toolbar);
        
        List<MenuItem*> items;

    public:
        Toolbar(Ghurund::UI::StyleWithLayout<Toolbar, ToolbarLayout>* style);

        ~Toolbar() {
            items.deleteItems();
        }

        inline List<MenuItem*>& getItems() {
            return items;
        }

        __declspec(property(get = getItems)) List<MenuItem*>& Items;

        inline static const Ghurund::Type& TYPE = TypeBuilder<Toolbar>(NAMESPACE_NAME, CLASS_NAME)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

    };
}