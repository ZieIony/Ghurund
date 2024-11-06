#include "ghuipch.h"
#include "DrawableAttr.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& DrawableAttr::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DrawableAttr>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Ghurund::Core::Type& DrawableValue::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DrawableValue>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    const Ghurund::Core::Type& DrawableRef::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<DrawableRef>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    IntrusivePointer<Drawable> DrawableRef::resolve(const Theme& theme) const {
        auto iterator = theme.Drawables.find(key);
        if (iterator == theme.Drawables.end()) {
            Logger::log(LogType::WARNING, std::format(_T("Drawable '{}' not found in the current theme.\n"), key.Value).c_str());
            return IntrusivePointer<Drawable>(nullptr);
        }
        return iterator->value->get();
    }

}
