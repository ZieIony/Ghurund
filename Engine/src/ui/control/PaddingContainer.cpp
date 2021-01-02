#include "PaddingContainer.h"
#include "ui/LayoutLoader.h"

#include <regex>

namespace Ghurund::UI {
    void PaddingContainer::onMeasure(float parentWidth, float parentHeight) {
        if (Child) {
            Child->measure(
                (preferredSize.width >= 0 ? (float)preferredSize.width : parentWidth) - padding.left - padding.right,
                (preferredSize.height >= 0 ? (float)preferredSize.height : parentHeight) - padding.top - padding.bottom
            );
        }

        if (preferredSize.width == PreferredSize::Width::WRAP) {
            measuredSize.width = padding.left + padding.right;
            if (Child)
                measuredSize.width += (float)Child->MeasuredSize.width;
        } else if (preferredSize.width != PreferredSize::Width::FILL) {
            measuredSize.width = (float)preferredSize.width;
        }

        if (preferredSize.height == PreferredSize::Height::WRAP) {
            measuredSize.height = padding.top + padding.bottom;
            if (Child)
                measuredSize.height += (float)Child->MeasuredSize.height;
        } else if (preferredSize.height != PreferredSize::Height::FILL) {
            measuredSize.height = (float)preferredSize.height;
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

    Status PaddingContainer::load(LayoutLoader& loader, ResourceContext& context, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, context, xml);
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