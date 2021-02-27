#pragma once

#include "TreeRowBinding.h"
#include "ui/control/ControlContainer.h"
#include "ui/control/ImageView.h"
#include "ui/layout/LinearLayout.h"
#include "ui/widget/ContainerWidget.h"

namespace Ghurund::UI {
    class TreeRow:public ContainerWidget<TreeRowBinding> {
    private:
        TreeItem* item;

    public:

    };
}