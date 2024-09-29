#include "ghedxpch.h"
#include "DirectXDrawingContext.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::Engine::DirectX::DirectXDrawingContext>() {
        static Type TYPE = TypeBuilder<Ghurund::Engine::DirectX::DirectXDrawingContext>(Ghurund::Engine::DirectX::NAMESPACE_NAME, GH_STRINGIFY(DirectXDrawingContext));
        return TYPE;
    }
}