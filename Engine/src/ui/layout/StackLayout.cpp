#include "StackLayout.h"
#include "ui/LayoutLoader.h"

namespace Ghurund::UI {
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
