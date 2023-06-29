#include "ghuipch.h"
#include "Shape.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& Shape::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<Shape>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<Shape>(NAMESPACE_NAME, GH_STRINGIFY(Shape))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}