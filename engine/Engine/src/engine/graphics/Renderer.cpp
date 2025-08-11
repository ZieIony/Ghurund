#include "ghepch.h"
#include "Renderer.h"

#include "core/reflection/Property.h"

namespace Ghurund::Engine {
    const Ghurund::Core::Type& Renderer::GET_TYPE() {
        static auto PROPERTY_STATISTICS = Ghurund::Core::Property<Renderer, RenderingStatistics&>("Statistics", &getStatistics);
      
        static const Ghurund::Core::Type TYPE = Ghurund::Core::TypeBuilder<Renderer>()
            .withProperty(PROPERTY_STATISTICS)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}