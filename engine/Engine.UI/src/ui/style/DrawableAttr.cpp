#include "ghuipch.h"
#include "DrawableAttr.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& DrawableAttr::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DrawableAttr>(NAMESPACE_NAME, GH_STRINGIFY(DrawableAttr))
            .withModifier(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    Drawable* DrawableRef::resolve(const Theme& theme) const {
        size_t index = theme.Drawables.indexOfKey(key);
        if (index == theme.Drawables.Size) {
            Logger::log(LogType::WARNING, std::format(_T("Drawable '{}' not found in the current theme.\n"), key.Value).c_str());
            return nullptr;
        }
        return theme.Drawables.getValue(index)->get();
    }

}
