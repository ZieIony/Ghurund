#pragma once

namespace Ghurund::UI {
    class Canvas;

    class DrawingCache {
    public:
        virtual ~DrawingCache() {}

        virtual void draw(Canvas& canvas) const = 0;
    };
}