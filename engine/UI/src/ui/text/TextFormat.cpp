#include "ghuipch.h"
#include "TextFormat.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& TextFormat::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<TextFormat>(NAMESPACE_NAME, GH_STRINGIFY(TextFormat))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    TextFormat::~TextFormat() {
        if (font)
            font->release();
    }
}