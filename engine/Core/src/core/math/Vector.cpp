#include "ghcpch.h"
#include "Vector.h"

#include "core/string/TextConversionUtils.h"

#include <regex>

namespace Ghurund::Core {
    template<>
    ::DirectX::XMFLOAT3 parse(const WString& text) {
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
