#include "ghuipch.h"
#include "MenuItem.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {

    template<>
    const Type& getType<Ghurund::UI::MenuItem>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::MenuItem>(NAMESPACE_NAME, GH_STRINGIFY(MenuItem));
        return TYPE;
    }

    template<>
    const Type& getType<Ghurund::UI::ButtonMenuItem>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::ButtonMenuItem>(NAMESPACE_NAME, GH_STRINGIFY(ButtonMenuItem));
        return TYPE;
    }

    template<>
    const Type& getType<Ghurund::UI::SeparatorMenuItem>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::SeparatorMenuItem>(NAMESPACE_NAME, GH_STRINGIFY(SeparatorMenuItem));
        return TYPE;
    }
}