#include "ghuipch.h"
#include "StackLayout.h"

#include "ui/loading/LayoutLoader.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& StackLayout::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<StackLayout>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<StackLayout>(NAMESPACE_NAME, GH_STRINGIFY(StackLayout))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
    void Ghurund::UI::StackLayout::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        __super::load(loader, xml);
        Ghurund::UI::Alignment a;
        if (loader.loadAlignment(xml, &a) == Status::OK)
            Alignment = a;
    }
}
