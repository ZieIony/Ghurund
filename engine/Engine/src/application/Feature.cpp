#include "ghpch.h"
#include "Feature.h"

namespace Ghurund {
    inline const Ghurund::Core::Type& Feature::GET_TYPE() {

        static const Ghurund::Core::Type TYPE = TypeBuilder<Feature>(Ghurund::NAMESPACE_NAME, "Feature")
            .withModifier(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
