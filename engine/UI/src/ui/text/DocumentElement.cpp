#include "ghuipch.h"
#include "DocumentElement.h"

#include "ui/loading/LayoutLoader.h"

namespace Ghurund::UI {
	void DocumentElementGroup::load(Ghurund::UI::LayoutLoader& loader, const XMLElement& xml) {
		for (const auto& child : xml.children) {
			DocumentElement* element = loader.loadDocumentElement(child.ref());
			if (element)
				elements.add(element);
		};
	}
}
