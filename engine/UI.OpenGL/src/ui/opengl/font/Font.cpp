#include "ghuioglpch.h"
#include "Font.h"

#include "core/reflection/TypeBuilder.h"
#include "core/reflection/Property.h"
#include "core/reflection/StandardTypes.h"

namespace Ghurund::UI::OpenGL
{
    const Ghurund::Core::Type& Font::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Font>();

        static const Ghurund::Core::Type TYPE = TypeBuilder<Font>(Ghurund::UI::OpenGL::NAMESPACE_NAME, "Font")
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

}