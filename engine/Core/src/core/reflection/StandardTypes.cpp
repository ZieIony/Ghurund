#include "ghcpch.h"
#include "Common.h"
#include "StandardTypes.h"

namespace Ghurund::Core {

    template<>
    const Type& getType<void>() {
        static Type TYPE = Type("void", 0);
        return TYPE;
    }

    template<>
    const Type& getType<int32_t>() {
        static Type TYPE = TypeBuilder<int32_t>();
        return TYPE;
    }

    template<>
    const Type& getType<uint32_t>() {
        static Type TYPE = TypeBuilder<uint32_t>();
        return TYPE;
    }

    template<>
    const Type& getType<float>() {
        static Type TYPE = TypeBuilder<float>();
        return TYPE;
    }

    template<>
    const Type& getType<bool>() {
        static Type TYPE = TypeBuilder<bool>();
        return TYPE;
    }

    template<>
    const Type& getType<char>() {
        static Type TYPE = TypeBuilder<char>();
        return TYPE;
    }

    template<>
    const Type& getType<wchar_t>() {
        static Type TYPE = TypeBuilder<wchar_t>();
        return TYPE;
    }

    template<>
    const Type& getType<AString>() {
        static Type TYPE = TypeBuilder<AString>()
            .withTemplateParam<char>();
        return TYPE;
    }

    template<>
    const Type& getType<WString>() {
        static Type TYPE = TypeBuilder<WString>()
            .withTemplateParam<wchar_t>();
        return TYPE;
    }

    template<>
    const Type& getType<IntSize>() {
        static Type TYPE = TypeBuilder<IntSize>()
            .withTemplateParam<uint32_t>();
        return TYPE;
    }

    template<>
    const Type& getType<FloatSize>() {
        static Type TYPE = TypeBuilder<FloatSize>()
            .withTemplateParam<float>();
        return TYPE;
    }

    template<>
    const Type& getType<IntPoint>() {
        static Type TYPE = TypeBuilder<IntPoint>();
        return TYPE;
    }

    template<>
    const Type& getType<FloatPoint>() {
        static Type TYPE = TypeBuilder<FloatPoint>();
        return TYPE;
    }

    template<>
    const Type& getType<Matrix3x2>() {
        static Type TYPE = TypeBuilder<Matrix3x2>();
        return TYPE;
    }

    template<>
    const Type& getType<Buffer>() {
        static Type TYPE = TypeBuilder<Buffer>();
        return TYPE;
    }

    template<>
    const Type& getType<DirectX::XMINT2>() {
        static Type TYPE = TypeBuilder<DirectX::XMINT2>();
        return TYPE;
    }

    template<>
    const Type& getType<DirectX::XMFLOAT2>() {
        static Type TYPE = TypeBuilder<DirectX::XMFLOAT2>();
        return TYPE;
    }

    template<>
    const Type& getType<DirectX::XMFLOAT3>() {
        static Type TYPE = TypeBuilder<DirectX::XMFLOAT3>();
        return TYPE;
    }

    template<>
    const Type& getType<DirectX::XMFLOAT4>() {
        static Type TYPE = TypeBuilder<DirectX::XMFLOAT4>();
        return TYPE;
    }

    template<>
    const Type& getType<DirectX::XMFLOAT4X4>() {
        static Type TYPE = TypeBuilder<DirectX::XMFLOAT4X4>();
        return TYPE;
    }
}