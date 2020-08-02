#pragma once

#include "Font.h"
#include "Paint.h"

namespace Ghurund {
    __interface Canvas {
        void beginPaint();
        void endPaint();
        void clear(unsigned int color);

        void drawRect(float x, float y, float width, float height, const Paint& paint);
        void fillRect(float x, float y, float width, float height, const Paint& paint);

        void drawLine(float x1, float y1, float x2, float y2, const Paint& paint);

        void drawText(const String& text, float x, float y, float width, float height, const Ghurund::Font& font, const Paint& paint);

        void translate(float x, float y);
    };
}