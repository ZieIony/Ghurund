#include "ghpch.h"
#include "MathTypes.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<DirectX::XMFLOAT2>() {
        static Type TYPE = Type("DirectX", "XMFLOAT2", sizeof(DirectX::XMFLOAT2));
        return TYPE;
    }

    template<>
    const Type& getType<DirectX::XMFLOAT3>() {
        static Type TYPE = Type("DirectX", "XMFLOAT3", sizeof(DirectX::XMFLOAT3));
        return TYPE;
    }

    template<>
    const Type& getType<DirectX::XMFLOAT4>() {
        static Type TYPE = Type("DirectX", "XMFLOAT4", sizeof(DirectX::XMFLOAT4));
        return TYPE;
    }
}