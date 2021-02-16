#pragma once

#include "TreeItem.h"
#include "TreeRow.h"

#include "ui/adapter/RecyclerView.h"
#include "ui/adapter/ItemAdapter.h"
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
}