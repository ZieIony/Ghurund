#pragma once

#include "TreeItem.h"
#include "TreeRow.h"

#include "ui/adapter/AdapterLayout.h"

namespace Ghurund::UI {
    class TreeRowAdapter:public ItemAdapter {
    public:
        TreeRowAdapter() {}

        virtual TreeRow* makeControl() const {
            return ghnew TreeRow();
        }
    };

    class TreeView:public ControlContainer {
    private:
        AdapterLayout* recycler;
        TreeRowAdapter* adapter;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        TreeView() {
            //recycler = ghnew AdapterLayout();
            //recycler->LayoutManager = std::unique_ptr< VerticalLayoutManager>(ghnew VerticalLayoutManager());
            //auto provider = ghnew TreeChildrenProvider();
            //recycler->ControlProvider = std::unique_ptr<TreeChildrenProvider>(provider);
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

    typedef IntrusivePointer<TreeView> TreeViewPtr;
}