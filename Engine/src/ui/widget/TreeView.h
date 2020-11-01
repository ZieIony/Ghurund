#pragma once

#include "ui/control/ControlContainer.h"
#include "ui/control/ImageView.h"
#include "ui/control/RecyclerView.h"
#include "ui/layout/LinearLayout.h"

namespace Ghurund::UI {
    class TreeItem {
    public:
        TreeItem* parent = nullptr;
        List<TreeItem*> children;

        inline uint32_t getDepth() {
            uint32_t depth = 0;
            TreeItem* p = parent;
            while (p) {
                depth++;
                p = parent->parent;
            }
            return depth;
        }
    };

    class TreeRow:public HorizontalLayout {
    private:
        ImageViewPtr imageView;
        ControlContainerPtr container;

    public:
        TreeRow() {
            imageView = ghnew ImageView();
            container = ghnew ControlContainer();
            container->PreferredSize.width = PreferredSize::Width::FILL;
            Children = { imageView, container };
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