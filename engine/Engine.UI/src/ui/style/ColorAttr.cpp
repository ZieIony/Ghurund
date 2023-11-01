#include "ghuipch.h"
#include "ColorAttr.h"

#include "ui/control/Control.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ColorAttr::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Pointer>(NAMESPACE_NAME, GH_STRINGIFY(ColorAttr))
            .withModifiers(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Ghurund::Core::Type& ColorValue::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Pointer>(NAMESPACE_NAME, GH_STRINGIFY(ColorValue))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Ghurund::Core::Type& ColorRef::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<Pointer>(NAMESPACE_NAME, GH_STRINGIFY(ColorRef))
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Color* ColorRef::resolve(const Theme& theme) const {
        auto iterator = theme.Colors.find(key);
        if (iterator == theme.Colors.end()) {
            Logger::log(LogType::WARNING, std::format(_T("Color '{}' not found in the current theme.\n"), key.Value).c_str());
            return nullptr;
        }
        return &iterator->value;
    }
}

namespace Ghurund::Core {

    template<>
    const Type& getType<Ghurund::UI::ColorAttr>() {
        static Type TYPE = TypeBuilder<Ghurund::UI::ColorAttr>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(Ghurund::UI::ColorAttr));
        return TYPE;
    }
}
