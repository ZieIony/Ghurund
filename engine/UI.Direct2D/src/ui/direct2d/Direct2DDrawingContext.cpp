#include "ghuid2dpch.h"
#include "Direct2DDrawingContext.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Direct2D::Direct2DDrawingContext>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::Direct2D::Direct2DDrawingContext>(Ghurund::UI::Direct2D::NAMESPACE_NAME, GH_STRINGIFY(Direct2DDrawingContext));
        return TYPE;
    }
}