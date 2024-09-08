#include "ghuipch.h"
#include "DocumentElement.h"

#include "ui/Canvas.h"
#include "ui/loading/LayoutLoader.h"

namespace Ghurund::UI {
    void DocumentElementGroup::load(Ghurund::UI::LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        auto child = xml.FirstChildElement();
        while (child) {
            DocumentElement* element = loader.loadDocumentElement(*child);
            if (element)
                elements.add(element);
            child = child->NextSiblingElement();
        };
    }
}
