#include "ghuipch.h"
#include "Alignment.h"

#include <regex>

namespace Ghurund::UI {
    Alignment Alignment::parse(const Ghurund::Core::AString& alignment) {
        Alignment result;
        Ghurund::Core::AString str = alignment.toLowerCase();
        std::regex regex(" *(left|center|right) *, *(top|center|bottom) *");
        std::smatch m;
        std::string s = str.Data;
        if (std::regex_match(s, m, regex)) {
            if (m[1].str() == "left") {
                result.horizontal = Alignment::Horizontal::LEFT;
            } else if (m[1].str() == "center") {
                result.horizontal = Alignment::Horizontal::CENTER;
            } else if (m[1].str() == "right") {
                result.horizontal = Alignment::Horizontal::RIGHT;
            }
            if (m[2].str() == "top") {
                result.vertical = Alignment::Vertical::TOP;
            } else if (m[2].str() == "center") {
                result.vertical = Alignment::Vertical::CENTER;
            } else if (m[2].str() == "bottom") {
                result.vertical = Alignment::Vertical::BOTTOM;
            }
        } else {
            throw std::invalid_argument("invalid alignment string");
        }
        return result;
    }
}