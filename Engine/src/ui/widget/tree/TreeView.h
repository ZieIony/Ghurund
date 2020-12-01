#pragma once

#include "TreeItem.h"
#include "TreeRow.h"

#include "ui/adapter/RecyclerView.h"
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
        RecyclerView<TreeItem*, TreeRow>* recycler;
        List<TreeItem*> items;
        TreeRowAdapter adapter;

    public:
        TreeView() {
            recycler = ghnew RecyclerView<TreeItem*, TreeRow>();
            recycler->LayoutManager = ghnew VerticalLayoutManager();
            recycler->Adapters.add(&adapter);
            recycler->Items = ghnew ListItemSource<TreeItem*>(items);
            Child = recycler;
        }

        ~TreeView() {
            recycler->release();
        }

    };

    typedef SharedPointer<TreeView> TreeViewPtr;
}