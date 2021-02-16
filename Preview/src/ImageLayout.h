#pragma once

#include "core/collection/PointerList.h"
#include "ui/LayoutLoader.h"
#include "ui/control/ControlContainer.h"

namespace Preview {
    using namespace Ghurund;
    using namespace Ghurund::UI;

    class ImageLayout:public ControlContainer {
    public:
        void init(LayoutLoader& layoutLoader) {
            PointerList<Control*> controls;
            layoutLoader.load(L"Preview/imageLayout.xml", controls);
            Child = controls[0];
        }
    };
}