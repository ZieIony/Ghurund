#pragma once

#include "core/collection/PointerList.h"
#include "core/resource/Resource.h"
#include "ui/control/Control.h"

#include "reflection_cd0693ee_78df_4af5_8047_ae9f4f2a44af.h"

namespace Ghurund::UI {
    class Layout:public Resource {
        reflection_cd0693ee_78df_4af5_8047_ae9f4f2a44af

    private:
        PointerList<Control*> controls;

    public:
        PointerList<Control*>& getControls() {
            return controls;
        }

        __declspec(property(get = getControls)) PointerList<Control*>& Controls;
    };
}