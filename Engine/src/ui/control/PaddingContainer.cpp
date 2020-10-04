#include "PaddingContainer.h"

namespace Ghurund::UI {
    void PaddingContainer::onMeasure(float parentWidth, float parentHeight) {
        if (Child) {
            Child->measure(
                (preferredSize.width >= 0 ? preferredSize.width : parentWidth) - padding.left - padding.right,
                (preferredSize.height >= 0 ? preferredSize.height : parentHeight) - padding.top - padding.bottom
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
}