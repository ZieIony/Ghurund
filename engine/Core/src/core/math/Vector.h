#pragma once

#include <DirectXMath.h>

namespace Ghurund::Core {
    using namespace ::DirectX;

    template<typename V>
    inline XMVECTOR __fastcall XMLoadFloatN(const V* source) noexcept;

    template<>
    inline XMVECTOR __fastcall XMLoadFloatN(const XMFLOAT2* source) noexcept {
        return XMLoadFloat2(source);
    }

    template<>
    inline XMVECTOR __fastcall XMLoadFloatN(const XMFLOAT3* source) noexcept {
        return XMLoadFloat3(source);
    }

    template<typename V>
    inline void __fastcall XMStoreFloatN(V* destination, FXMVECTOR source) noexcept;

    template<>
    inline void __fastcall XMStoreFloatN(XMFLOAT2* destination, FXMVECTOR source) noexcept {
        XMStoreFloat2(destination, source);
    }

    template<>
    inline void __fastcall XMStoreFloatN(XMFLOAT3* destination, FXMVECTOR source) noexcept {
        XMStoreFloat3(destination, source);
    }

    template<typename V>
    inline XMVECTOR __fastcall XMVectorNLengthSq(FXMVECTOR v) noexcept;

    template<XMFLOAT3>
    inline XMVECTOR __fastcall XMVectorNLengthSq(FXMVECTOR v) noexcept {
        return XMVector2LengthSq(v);
    }

    template<XMFLOAT2>
    inline XMVECTOR __fastcall XMVectorNLengthSq(FXMVECTOR v) noexcept {
        return XMVector3LengthSq(v);
    }
}