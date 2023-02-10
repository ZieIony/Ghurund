#include "ghuipch.h"
#include "TextDocument.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::TextDocument>() {
        static Type TYPE = Type(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(TextDocument), sizeof(Ghurund::UI::TextDocument));
        return TYPE;
    }
}
