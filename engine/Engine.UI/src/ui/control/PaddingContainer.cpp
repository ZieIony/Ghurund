#include "ghuipch.h"
#include "PaddingContainer.h"

#include "ui/layout/LayoutLoader.h"

#include <regex>

namespace Ghurund::UI {
    const Ghurund::Type& PaddingContainer::GET_TYPE() {
        static const auto CONSTRUCTOR = NoArgsConstructor<PaddingContainer>();
        static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(PaddingContainer))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void PaddingContainer::onMeasure(float parentWidth, float parentHeight) {
        if (Child) {
            Child->measure(
                (preferredSize.width >= 0 ? (float)preferredSize.width : parentWidth) - padding.left - padding.right,
                (preferredSize.height >= 0 ? (float)preferredSize.height : parentHeight) - padding.top - padding.bottom
            );
        }

        measuredSize.width = std::max(minSize.width, (float)preferredSize.width);
        measuredSize.height = std::max(minSize.height, (float)preferredSize.height);
        if (Child) {
            float childWidth = (float)Child->PreferredSize.width >= 0 ? (float)Child->PreferredSize.width : Child->MeasuredSize.width;
            measuredSize.width = std::max(measuredSize.width, padding.left + padding.right + childWidth);
            float childHeight = (float)Child->PreferredSize.height >= 0 ? (float)Child->PreferredSize.height : Child->MeasuredSize.height;
            measuredSize.height = std::max(measuredSize.height, padding.top + padding.bottom + childHeight);
        } else {
            measuredSize.width = std::max(measuredSize.width, padding.left + padding.right);
            measuredSize.height = std::max(measuredSize.height, padding.top + padding.bottom);
        }
    }

    void PaddingContainer::onLayout(float x, float y, float width, float height) {
        if (Child) {
            Child->layout(
                padding.left,
                padding.top,
                std::max(width - padding.left - padding.right, Child->MinSize.width),
                std::max(height - padding.top - padding.bottom, Child->MinSize.height)
            );
        }
    }

    Status PaddingContainer::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, xml);
        if (result != Status::OK)
            return result;
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
        return Status::OK;
    }
}