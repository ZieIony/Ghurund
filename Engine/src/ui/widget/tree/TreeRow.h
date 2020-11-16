#pragma once

#include "ui/control/ControlContainer.h"
#include "ui/control/ImageView.h"
#include "ui/layout/LinearLayout.h"

namespace Ghurund::UI {
    class TreeRow:public HorizontalLayout {
    private:
        ScopedPointer<ImageView> imageView;
        ScopedPointer<ControlContainer> container;

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
}