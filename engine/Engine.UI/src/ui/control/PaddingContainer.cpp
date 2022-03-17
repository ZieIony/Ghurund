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

    void PaddingContainer::onMeasure(float parentWidth, float parentHeight) {
        /*if (Child) {
            Child->measure(
                (preferredSize.width.Type == PreferredSize::Type::PIXELS ? preferredSize.width.Value : parentWidth) - padding.left - padding.right,
                (preferredSize.height.Type == PreferredSize::Type::PIXELS ? preferredSize.height.Value : parentHeight) - padding.top - padding.bottom
            );
        }

        if (preferredSize.width.Type == PreferredSize::Type::PIXELS)
            measuredSize.Width = std::max(minSize.Width, preferredSize.width.Value);
        if (preferredSize.height.Type == PreferredSize::Type::PIXELS)
            measuredSize.Height = std::max(minSize.Height, preferredSize.height.Value);
        if (Child) {
            float childWidth = Child->PreferredSize.width.Type == PreferredSize::Type::PIXELS ? Child->PreferredSize.width.Value : Child->MeasuredSize.Width;
            measuredSize.Width = std::max(measuredSize.Width, padding.left + padding.right + childWidth);
            float childHeight = Child->PreferredSize.height.Type == PreferredSize::Type::PIXELS ? Child->PreferredSize.height.Value : Child->MeasuredSize.Height;
            measuredSize.Height = std::max(measuredSize.Height, padding.top + padding.bottom + childHeight);
        } else {
            measuredSize.Width = std::max(measuredSize.Width, padding.left + padding.right);
            measuredSize.Height = std::max(measuredSize.Height, padding.top + padding.bottom);
        }*/
    }

    void PaddingContainer::onLayout(float x, float y, float width, float height) {
        /*if (Child) {
            Child->layout(
                padding.left,
                padding.top,
                std::max(width - padding.left - padding.right, Child->MinSize.Width),
                std::max(height - padding.top - padding.bottom, Child->MinSize.Height)
            );
        }*/
    }

    void PaddingContainer::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        __super::load(loader, xml);
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