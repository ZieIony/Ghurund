#include "ghuipch.h"
#include "LayoutAttr.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& LayoutAttr::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<LayoutAttr>(NAMESPACE_NAME, GH_STRINGIFY(LayoutAttr))
            .withModifier(TypeModifier::ABSTRACT)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
    
    SharedPointer<Control> LayoutRef::resolve(const Theme& theme) const {
        size_t index = theme.Layouts.indexOfKey(key);
        if (index == theme.Layouts.Size) {
            Logger::log(LogType::WARNING, std::format(_T("Layout '{}' not found in the current theme.\n"), key.Value).c_str());
            return SharedPointer<Control>(nullptr);
        }
        return theme.Layouts.getValue(index)->get();
    }
}
