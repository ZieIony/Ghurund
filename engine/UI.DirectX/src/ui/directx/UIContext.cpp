#include "ghuidxpch.h"
#include "UIContext.h"

#include <core/reflection/TypeBuilder.h>

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::DirectX::UiContext>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::DirectX::UiContext>();
        return TYPE;
    }
}