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

    template<class T>
    class TreeItemSource:public ItemSource<TreeItem*> {
    private:
        List<T>& list;

    public:
        TreeItemSource(List<T>& list):list(list) {}

        virtual size_t getSize() const override {
            return list.Size;
        }

        virtual T& get(size_t position) const override {
            return list.get(position);
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