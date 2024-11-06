#include "ghuioglpch.h"
#include "Font.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI::OpenGL
{
    const Ghurund::Core::Type& Font::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Font>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

}