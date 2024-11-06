#include "ghedxpch.h"
#include "DirectXDrawingContext.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::Engine::DirectX::DirectXDrawingContext>() {
        static const Type TYPE = TypeBuilder<Ghurund::Engine::DirectX::DirectXDrawingContext>();
        return TYPE;
    }
}