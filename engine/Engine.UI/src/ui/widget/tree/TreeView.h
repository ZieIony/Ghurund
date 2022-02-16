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
        TreeRowAdapter adapter;

        typedef SingleAdapterChildrenProvider<TreeItem*, TreeRow, TreeRowAdapter> TreeChildrenProvider;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        TreeView() {
            recycler = ghnew RecyclerView();
            recycler->LayoutManager = std::unique_ptr< VerticalLayoutManager>(ghnew VerticalLayoutManager());
            auto provider = ghnew TreeChildrenProvider();
            recycler->ChildrenProvider = std::unique_ptr<TreeChildrenProvider>(provider);
            Child = recycler;
        }

        ~TreeView() {
            recycler->release();
        }

        

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };

    typedef SharedPointer<TreeView> TreeViewPtr;
}