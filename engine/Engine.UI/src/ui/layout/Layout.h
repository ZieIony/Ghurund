#pragma once

#include "core/collection/PointerList.h"
#include "core/resource/Resource.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
    class Layout:public Ghurund::Core::Resource {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

    private:
        PointerList<Control*> controls;

    public:
        PointerList<Control*>& getControls() {
            return controls;
        }

        __declspec(property(get = getControls)) PointerList<Control*>& Controls;

        static const inline Ghurund::Core::ResourceFormat FORMAT_XML = Ghurund::Core::ResourceFormat(L"xml", true, false);

        inline static const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& FORMATS = { FORMAT_XML };

        virtual const Ghurund::Core::Array<Ghurund::Core::ResourceFormat>& getFormats() const override {
            return FORMATS;
        }
    };
}