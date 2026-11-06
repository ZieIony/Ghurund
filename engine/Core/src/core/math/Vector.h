#pragma once

#include "core/DataParsing.h"
#include "core/math/Float.h"

#include <DirectXMath.h>
#include <regex>

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

    inline bool operator==(const XMINT2& v1, const XMINT2& v2) {
        return v1.x == v2.x && v1.y == v2.y;
    }

    inline bool operator==(const XMFLOAT2& v1, const XMFLOAT2& v2) {
        return v1.x == v2.x && v1.y == v2.y;
    }

    inline bool operator==(const XMFLOAT3& v1, const XMFLOAT3& v2) {
        return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
    }

    template<>
    inline ::DirectX::XMFLOAT3 parse(const WString& text) {
        auto str = convertText<wchar_t, char>(text);
        std::regex regex(" *(\\d+(?:\\.\\d+)?) *, *(\\d+(?:\\.\\d+)?) *, *(\\d+(?:\\.\\d+)?) *");
        std::smatch m;
        std::string s = str.Data;
        if (std::regex_match(s, m, regex)) {
            float x = Ghurund::Core::parse<float>(m[1].str().c_str());
            float y = Ghurund::Core::parse<float>(m[2].str().c_str());
            float z = Ghurund::Core::parse<float>(m[3].str().c_str());
            return { x, y, z };
        } else {
            throw std::invalid_argument("invalid float3 string");
        }
    }

}
