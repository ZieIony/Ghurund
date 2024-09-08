#include "ghepch.h"

#include "RenderingStatistics.h"

#include "Ghurund.Engine.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<RenderingStatistics>() {
        static Type TYPE = Type(Ghurund::Engine::NAMESPACE_NAME, "RenderingStatistics", sizeof(RenderingStatistics));
        return TYPE;
    }
}