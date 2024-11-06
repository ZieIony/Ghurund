#include "ghuipch.h"
#include "MenuItem.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {

    template<>
    const Type& getType<Ghurund::UI::MenuItem>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::MenuItem>();
        return TYPE;
    }

    template<>
    const Type& getType<Ghurund::UI::ButtonMenuItem>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::ButtonMenuItem>();
        return TYPE;
    }

    template<>
    const Type& getType<Ghurund::UI::SeparatorMenuItem>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::SeparatorMenuItem>();
        return TYPE;
    }
}