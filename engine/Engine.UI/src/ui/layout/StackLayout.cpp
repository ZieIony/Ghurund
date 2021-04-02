#include "ghuipch.h"
#include "StackLayout.h"

#include "ui/LayoutLoader.h"

namespace Ghurund::UI {
    const Ghurund::Type& StackLayout::GET_TYPE() {
        static const auto CONSTRUCTOR = Ghurund::NoArgsConstructor<StackLayout>();
        static const Ghurund::Type TYPE = Ghurund::TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(StackLayout))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
    Status Ghurund::UI::StackLayout::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, xml);
        if (result != Status::OK)
            return result;
        Ghurund::UI::Alignment a;
        if (loader.loadAlignment(xml, &a) == Status::OK)
            Alignment = a;
        return Status::OK;
    }
}
