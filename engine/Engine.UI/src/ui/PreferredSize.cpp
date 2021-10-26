#include "ghuipch.h"
#include "PreferredSize.h"

namespace Ghurund::UI {
    const PreferredSize::Width& PreferredSize::Width::WRAP = PreferredSize::Width(PreferredSize::Type::WRAP, 0.0f);
    const PreferredSize::Height& PreferredSize::Height::WRAP = PreferredSize::Height(PreferredSize::Type::WRAP, 0.0f);
    const PreferredSize::Width& PreferredSize::Width::FILL = PreferredSize::Width(PreferredSize::Type::FILL, 0.0f);
    const PreferredSize::Height& PreferredSize::Height::FILL = PreferredSize::Height(PreferredSize::Type::FILL, 0.0f);
    
    PreferredSize PreferredSize::parse(const Ghurund::Core::AString& str) {
        PreferredSize size;
        std::regex regex(" *(\\d+(?:\\.\\d+)?\\%?|wrap|fill) *, *(\\d+(?:\\.\\d+)?\\%?|wrap|fill) *");
        std::smatch m;
        std::string s = str.Data;
        if (std::regex_match(s, m, regex)) {
            if (m[1].str() == "wrap") {
                size.width = PreferredSize::Width::WRAP;
            } else if (m[1].str() == "fill") {
                size.width = PreferredSize::Width::FILL;
            } else if (m[1].str().ends_with("%")) {
                float value = (float)atof(m[1].str().substr(0, m[1].str().length() - 1).c_str());
                size.width = PreferredSize::Width(PreferredSize::Type::PERCENT, value);
            } else {
                size.width = (float)atof(m[1].str().c_str());
            }
            if (m[2].str() == "wrap") {
                size.height = PreferredSize::Height::WRAP;
            } else if (m[2].str() == "fill") {
                size.height = PreferredSize::Height::FILL;
            } else if (m[2].str().ends_with("%")) {
                float value = (float)atof(m[2].str().substr(0, m[2].str().length() - 1).c_str());
                size.height = PreferredSize::Height(PreferredSize::Type::PERCENT, value);
            } else {
                size.height = (float)atof(m[2].str().c_str());
            }
        } else {
            throw std::invalid_argument("invalid size string");
        }
        return size;
    }
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::PreferredSize>() {
        static Type TYPE = Type(Ghurund::UI::NAMESPACE_NAME, "PreferredSize", sizeof(Ghurund::UI::PreferredSize));
        return TYPE;
    }
}