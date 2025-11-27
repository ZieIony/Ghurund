#include "ghedxpch.h"
#include "MathTypes.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<::DirectX::XMFLOAT2>() {
        static Type TYPE = TypeBuilder<::DirectX::XMFLOAT2>();
        return TYPE;
    }

    template<>
    const Type& getType<::DirectX::XMFLOAT3>() {
        static Type TYPE = TypeBuilder<::DirectX::XMFLOAT3>();
        return TYPE;
    }

    template<>
    const Type& getType<::DirectX::XMFLOAT4>() {
        static Type TYPE = TypeBuilder<::DirectX::XMFLOAT4>();
        return TYPE;
    }
}