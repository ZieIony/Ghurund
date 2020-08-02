#include "Control.h"

namespace Ghurund {
    void Control::measure() {
        if (desiredSize.x == LayoutSize::WRAP_CONTENT) {
            measuredSize.x = minSize.x;
        } else if (desiredSize.x == LayoutSize::MATCH_PARENT) {
            measuredSize.x = MAX_SIZE;
        } else {
            measuredSize.x = desiredSize.x;
        }

        if (desiredSize.y == LayoutSize::WRAP_CONTENT) {
            measuredSize.y = minSize.y;
        } else if (desiredSize.y == LayoutSize::MATCH_PARENT) {
            measuredSize.y = MAX_SIZE;
        } else {
            measuredSize.y = desiredSize.y;
        }
    }
}