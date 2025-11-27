#include "ghuipch.h"
#include "TextDocument.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::TextDocument>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::TextDocument>();
        return TYPE;
    }
}
