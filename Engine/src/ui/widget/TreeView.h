#pragma once

#include "core/ScopedPointer.h"
#include "ui/control/ImageView.h"
#include "ui/control/LinearLayout.h"
#include "ui/control/RecyclerView.h"

namespace Ghurund::UI {
    class TreeItem {
    public:
        TreeItem* parent;
        List<TreeItem*> children;
    };

    class TreeRow:public Row {
    private:
        ScopedPointer<ImageView> imageView;
        ScopedPointer<ControlContainer> container;

    public:
        TreeRow() {
            imageView = ghnew ImageView();
            container = ghnew ControlContainer();
            container->PreferredSize.width = PreferredSize::Width::FILL;
            Children.add({ imageView, container });
        }

        inline Control* getContent() {
            return container->Child;
        }

        inline void setContent(Control* control) {
            container->Child = control;
        }

        __declspec(property(get = getContent, put = setContent)) Control* Content;
    };

    class TreeView:public RecyclerView<TreeItem, TreeRow> {

    };
}