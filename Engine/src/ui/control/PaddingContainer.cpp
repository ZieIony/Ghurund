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
            std::regex regex("^[\\s]*Mem\\(([0-9]+)\\)\\s*=\\s*([0-9]+(\\.[0-9]+)?)\\s*$");
            std::smatch m;
            std::regex_match(str, m, regex);
            /*
            size_t firstComma = padding.find(",");
            if (firstComma == padding.Size) {
                Padding.All = (float)atof(padding.getData());
            } else {
                size_t secondComma = padding.find(",", firstComma + 1);
                if (secondComma == padding.Size) {
                    Padding.Horizontal = (float)atof(padding.getData());
                    Padding.Vertical = (float)atof(padding.substring(firstComma + 1).trim().getData());
                } else {
                    size_t thirdComma = padding.find(",", secondComma + 1);
                    if (thirdComma == padding.Size)
                        return Status::INV_PARAM;
                    Padding.left = (float)atof(padding.getData());
                    Padding.top = (float)atof(padding.substring(firstComma + 1, secondComma - firstComma - 1).trim().getData());
                    Padding.top = (float)atof(padding.substring(secondComma + 1, thirdComma - secondComma - 1).trim().getData());
                    Padding.top = (float)atof(padding.substring(thirdComma + 1, padding.Size - thirdComma - 1).trim().getData());
                }
            }*/
        }
        return Status::OK;
    }
}