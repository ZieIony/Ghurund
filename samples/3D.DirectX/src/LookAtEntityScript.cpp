#include "LookAtEntityScript.h"

namespace Sample {
    const Ghurund::Core::Type& LookAtEntityScript::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<LookAtEntityScript>();
      
        static const Ghurund::Core::Type TYPE = TypeBuilder<LookAtEntityScript>()
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
