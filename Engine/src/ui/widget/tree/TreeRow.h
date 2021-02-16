#pragma once

#include "TreeRowLayout.h"
#include "ui/control/ControlContainer.h"
#include "ui/control/ImageView.h"
#include "ui/layout/LinearLayout.h"
#include "ui/widget/ContentWidget.h"

namespace Ghurund::UI {
    class TreeRow:public ContentWidget<TreeRowLayout> {
    private:
        TreeItem* item;

    public:

    };
}