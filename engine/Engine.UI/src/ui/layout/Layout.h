#pragma once

#include "core/collection/PointerList.h"
#include "core/resource/Resource.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
    class Layout:public Ghurund::Core::Resource {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

        static const Array<ResourceFormat>& GET_FORMATS();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        inline static const Array<ResourceFormat>& FORMATS = GET_FORMATS();

        virtual const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& getFormats() const override {
            return FORMATS;
        }

    private:
        PointerList<Control*> controls;

    public:
        PointerList<Control*>& getControls() {
            return controls;
        }

        __declspec(property(get = getControls)) PointerList<Control*>& Controls;
    };
}