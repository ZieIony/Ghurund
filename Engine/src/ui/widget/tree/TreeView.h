#pragma once

#include "TreeItem.h"
#include "TreeRow.h"

#include "ui/adapter/RecyclerView.h"
#include "ui/adapter/AdapterChildrenProvider.h"
#include "ui/layout/VerticalLayoutManager.h"

namespace Ghurund::UI {
    class TreeRowAdapter:public ItemAdapter<TreeItem*, TreeRow> {
    public:
        TreeRowAdapter() {}

        virtual TreeRow* makeControl() const {
            return ghnew TreeRow();
        }
    };

    class TreeView:public ControlContainer {
    private:
        RecyclerView* recycler;
        List<TreeItem*> items;
        TreeRowAdapter adapter;

    protected:
        static const Ghurund::Type& GET_TYPE();

    public:
        TreeView() {
            recycler = ghnew RecyclerView();
            recycler->LayoutManager = ghnew VerticalLayoutManager();
            auto provider = ghnew AdapterChildrenProvider<TreeItem*, TreeRow>(*recycler);
            provider->Adapters.add(&adapter);
            provider->Items = ghnew ListItemSource<TreeItem*>(items);
            recycler->childrenProvider = provider;
            Child = recycler;
        }

        ~TreeView() {
            recycler->release();
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef SharedPointer<TreeView> TreeViewPtr;
}