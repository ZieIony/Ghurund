#include "ghpch.h"
#include "ExpandableContainer.h"

namespace Ghurund::UI {
    const Ghurund::Type& ExpandableContainer::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<ExpandableContainer>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ExpandableContainer))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }


    Status ExpandableContainer::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, xml);
        if (result != Status::OK)
            return result;
        Children.clear();
        Children.addAll(loader.loadControls(xml));
        return Status::OK;
    }
}