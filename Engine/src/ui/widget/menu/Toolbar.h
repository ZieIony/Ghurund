#pragma once

#include "ToolbarAdapter.h"
#include "ToolbarLayout.h"

#include "ui/Style.h"
#include "ui/adapter/RecyclerView.h"
#include "ui/control/ColorView.h"
#include "ui/layout/LinearLayout.h"
#include "ui/layout/HorizontalLayoutManager.h"

namespace Ghurund::UI {
    class Toolbar: public Widget<ToolbarLayout> {
    private:
        List<MenuItem*> items;

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Toolbar))
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    public:
        Toolbar(ToolbarLayout* layout):Widget(layout) {
            PreferredSize.height = PreferredSize::Height::WRAP;
            Layout.RecyclerView->Items = ghnew ListItemSource<MenuItem*>(items);
        }

        Toolbar(Ghurund::UI::Theme& theme):Toolbar(ghnew ToolbarLayout(theme)) {}

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

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

    };
}