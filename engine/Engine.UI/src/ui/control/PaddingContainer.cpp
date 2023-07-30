#include "ghuipch.h"
#include "PaddingContainer.h"

#include "ui/loading/LayoutLoader.h"

#include <regex>

namespace Ghurund::UI {
	const Ghurund::Core::Type& PaddingContainer::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<PaddingContainer>();
		static const Ghurund::Core::Type TYPE = TypeBuilder<PaddingContainer>(NAMESPACE_NAME, GH_STRINGIFY(PaddingContainer))
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	void PaddingContainer::onMeasure() {
		measuredSize.Width = width->Value + padding.left + padding.right;
		measuredSize.Height = height->Value + padding.top + padding.bottom;

		if (child)
			child->measure();
	}

	void PaddingContainer::onLayout(float x, float y, float width, float height) {
		if (Child) {
			Child->layout(
				padding.left,
				padding.top,
				width - padding.left - padding.right,
				height - padding.top - padding.bottom
			);
		}
	}

	void PaddingContainer::load(LayoutLoader& loader, ResourceManager& resourceManager, const tinyxml2::XMLElement& xml) {
		__super::load(loader, resourceManager, xml);
		auto paddingAttr = xml.FindAttribute("padding");
		if (paddingAttr) {
			std::string str = paddingAttr->Value();
			std::regex regex("(-?\\d+(?:\\.\\d+)?)(?:, *(-?\\d+(?:\\.\\d+)?)(?:, *(-?\\d+(?:\\.\\d+)?), *(-?\\d+(?:\\.\\d+)?))?)?");
			std::smatch m;
			if (std::regex_match(str, m, regex)) {
				if (!m[2].matched) {
					Padding.All = (float)atof(m[1].str().c_str());
				} else if (!m[3].matched) {
					Padding.Horizontal = (float)atof(m[1].str().c_str());
					Padding.Vertical = (float)atof(m[2].str().c_str());
				} else if (m[4].matched) {
					Padding.left = (float)atof(m[1].str().c_str());
					Padding.top = (float)atof(m[2].str().c_str());
					Padding.right = (float)atof(m[3].str().c_str());
					Padding.bottom = (float)atof(m[4].str().c_str());
				}
			}
		}
	}
}