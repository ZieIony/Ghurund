#include "ghuipch.h"
#include "DrawableAttr.h"

namespace Ghurund::UI {

    const Drawable* DrawableRef::resolve(const Theme& theme) const {
        size_t index = theme.Drawables.indexOfKey(key);
        if (index == theme.Drawables.Size) {
            Logger::log(LogType::WARNING, std::format(_T("Drawable '{}' not found in the current theme.\n"), key.Value).c_str());
            return nullptr;
        }
        return theme.Drawables.getValue(index).get();
    }

}
