#pragma once

#include "ToolbarAdapter.h"
#include "ToolbarBinding.h"

#include "ui/style/Style.h"
#include "ui/adapter/AdapterChildrenProvider.h"
#include "ui/adapter/RecyclerView.h"
#include "ui/control/ColorView.h"
#include "ui/layout/LinearLayout.h"
#include "ui/layout/HorizontalLayoutManager.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
    class Toolbar: public Widget<ToolbarBinding> {
    private:
        List<MenuItem*> items;

        static const Ghurund::Core::Type& GET_TYPE() {
            static const Ghurund::Core::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(Toolbar))
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        virtual void onLayoutChanged() override {
            /*auto provider = ghnew AdapterChildrenProvider<MenuItem*, Control>(*Layout->Recycler);
            provider->Adapters.add(ghnew ButtonToolbarAdapter());
            //provider->Adapters.add(ghnew SeparatorToolbarAdapter(theme));
            provider->Items = ghnew ListItemSource<MenuItem*>(items);
            Layout->Recycler->childrenProvider = provider;*/
        }

    public:
        Toolbar() {
            PreferredSize.height = PreferredSize::Height::WRAP;
        }

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

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}