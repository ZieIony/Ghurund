#pragma once

namespace Ghurund {
    class LayoutSize {
    private:
        LayoutSize() = delete;

    public:
        static inline const float WRAP_CONTENT = -1;
        static inline const float MATCH_PARENT = -2;
    };

    enum class HorizontalGravity {
        LEFT, RIGHT, CENTER
    };

    enum class VerticalGravity {
        TOP, BOTTOM, CENTER
    };

    struct Gravity {
        HorizontalGravity horizontal = HorizontalGravity::LEFT;
        VerticalGravity vertical = VerticalGravity::TOP;
    };
}