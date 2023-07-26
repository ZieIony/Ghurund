#pragma once

namespace Ghurund::UI {
    enum class ImageScaleMode {
        NONE, STRETCH, FIT, CROP
    };
}

namespace Ghurund::Core {
    class Type;

    template<>
    const Type& getType<Ghurund::UI::ImageScaleMode>();
}
