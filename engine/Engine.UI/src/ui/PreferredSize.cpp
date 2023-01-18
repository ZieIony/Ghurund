#include "ghuipch.h"
#include "PreferredSize.h"

#include "core/Float.h"

namespace Ghurund::UI {
    const PreferredSize::Width& PreferredSize::Width::WRAP = PreferredSize::Width(PreferredSize::Type::WRAP, 0.0f);
    const PreferredSize::Height& PreferredSize::Height::WRAP = PreferredSize::Height(PreferredSize::Type::WRAP, 0.0f);
    const PreferredSize::Width& PreferredSize::Width::FILL = PreferredSize::Width(PreferredSize::Type::FILL, 1.0f);
    const PreferredSize::Height& PreferredSize::Height::FILL = PreferredSize::Height(PreferredSize::Type::FILL, 1.0f);

    PreferredSize::Width PreferredSize::Width::parse(const Ghurund::Core::AString& str) {
        if (str == "wrap") {
            return PreferredSize::Width::WRAP;
        } else if (str == "fill") {
            return PreferredSize::Width::FILL;
        } else if (str.endsWith("%")) {
            float value = Ghurund::Core::parse<float>(str.substring(0, str.Length - 1));
            return PreferredSize::Width(PreferredSize::Type::PERCENT, value);
        } else {
            return Ghurund::Core::parse<float>(str);
        }
        throw std::invalid_argument("invalid size string");
    }

    PreferredSize::Height PreferredSize::Height::parse(const Ghurund::Core::AString& str) {
        if (str == "wrap") {
            return PreferredSize::Height::WRAP;
        } else if (str == "fill") {
            return PreferredSize::Height::FILL;
        } else if (str.endsWith("%")) {
            float value = Ghurund::Core::parse<float>(str.substring(0, str.Length - 1));
            return PreferredSize::Height(PreferredSize::Type::PERCENT, value);
        } else {
            return Ghurund::Core::parse<float>(str);
        }
        throw std::invalid_argument("invalid size string");
    }

    PreferredSize PreferredSize::parse(const Ghurund::Core::AString& str) {
        PreferredSize size;
        std::regex regex(" *(\\d+(?:\\.\\d+)?\\%?|wrap|fill) *, *(\\d+(?:\\.\\d+)?\\%?|wrap|fill) *");
        std::smatch m;
        std::string s = str.Data;
        if (std::regex_match(s, m, regex)) {
            size.width = Width::parse(m[1].str().c_str());
            size.height = Height::parse(m[2].str().c_str());
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