#include "ghuipch.h"
#include "Color.h"

#include <regex>

namespace Ghurund::UI {
    Color Ghurund::UI::Color::parse(const AString& color) {
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
            throw std::invalid_argument("invalid color string");
        }
        return Color(value);
    }
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::Color>() {
        static Type TYPE = Type(Ghurund::UI::NAMESPACE_NAME, "Color", sizeof(Ghurund::UI::Color));
        return TYPE;
    }
}