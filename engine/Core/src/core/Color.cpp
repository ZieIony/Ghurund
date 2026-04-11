#include "ghcpch.h"
#include "Color.h"

#include "core/reflection/Type.h"
#include "core/string/String.h"

#include <regex>

namespace Ghurund::Core {
    Color Color::parse(const AString& color) {
        uint32_t value = 0;
        AString str = color.toLowerCase();
        std::regex regex(" *\\#((?:[a-f0-9]{2})?[a-f0-9]{6}) *");
        std::smatch m;
        std::string s = str.Data;
        if (std::regex_match(s, m, regex)) {
            for (char c : m[0].str()) {
                if (c >= '0' && c <= '9') {
                    value = value * 16 + (c - '0');
                } else if (c >= 'a' && c <= 'f') {
                    value = value * 16 + (c - 'a' + 10);
                }
            }
        } else {
            throw InvalidParamException("invalid color string");
        }
        return Color(value);
    }

    template<>
    const Type& getType<Color>() {
        static Type TYPE = TypeBuilder<Color>();
        return TYPE;
    }

    String Color::toString() const {
        return String(std::format(_T("{:#010x}"), value).c_str());
    }
}
