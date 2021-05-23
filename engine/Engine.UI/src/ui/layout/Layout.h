#pragma once

#include "core/collection/PointerList.h"
#include "core/resource/Resource.h"
#include "ui/control/Control.h"

#include "reflection_79e1bf91_c323_405a_a25a_3007c1650e21.h"

namespace Ghurund::UI {
    class Layout:public Resource {
        reflection_79e1bf91_c323_405a_a25a_3007c1650e21

    private:
        PointerList<Control*> controls;

    public:
        PointerList<Control*>& getControls() {
            return controls;
        }

        __declspec(property(get = getControls)) PointerList<Control*>& Controls;

        static const inline ResourceFormat FORMAT_XML = ResourceFormat(L"xml", true, false);

        inline static const Array<ResourceFormat>& FORMATS = { FORMAT_XML };

        virtual const Array<ResourceFormat>& getFormats() const override {
            return FORMATS;
        }
    };
}