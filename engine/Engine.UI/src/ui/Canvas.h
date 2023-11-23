#pragma once

#include "Shape.h"
#include "StrokeStyle.h"
#include "core/Color.h"
#include "core/math/Rect.h"

#include <dxgi1_6.h>
#include <wrl.h>
#include <ui/image/Bitmap.h>
#include <ui/image/VectorImage.h>
#include <ui/text/TextLayout.h>

namespace Ghurund::UI {
    using Microsoft::WRL::ComPtr;
    using namespace Ghurund::Core;

    class ICanvas {
    public:
        virtual ~ICanvas()
        //    = 0   // TODO: a destructor cannot be abstract
        {}

        virtual bool isAntialiasingEnabled() = 0;

        virtual void setAntialiasingEnabled(bool enabled) = 0;

        __declspec(property(get = isAntialiasingEnabled, put = setAntialiasingEnabled)) bool AntialiasingEnabled;

        virtual void beginPaint() = 0;

        virtual void endPaint() = 0;

        virtual void clear(int32_t color) = 0;

        virtual void setColor(const Ghurund::UI::Color& color) = 0;

        __declspec(property(put = setColor)) Ghurund::UI::Color Color;

        virtual void drawRect(float x, float y, float width, float height, float thickness, IStrokeStyle* strokeStyle = nullptr) = 0;

        virtual void fillRect(float x, float y, float width, float height) = 0;

        virtual void drawShape(Ghurund::UI::Shape& shape, float thickness) = 0;

        virtual void drawLine(float x1, float y1, float x2, float y2, float thickness, IStrokeStyle* strokeStyle = nullptr) = 0;

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& dst, float alpha = 1.0f) = 0;

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& dst, const Ghurund::Core::Color& tint, float alpha = 1.0f) = 0;

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& src, const FloatRect& dst, float alpha = 1.0f) = 0;

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& src, const FloatRect& dst, const Ghurund::Core::Color& tint, float alpha = 1.0f) = 0;

        virtual void drawImage(VectorImage& vectorImage) = 0;

        virtual void drawText(TextLayout& layout, float x, float y) = 0;

        virtual void translate(float x, float y) = 0;

        virtual void save() = 0;

        virtual void restore() = 0;

        virtual void clipShape(Ghurund::UI::Shape& shape) = 0;

        virtual void restoreClipShape() = 0;

        virtual void clipRect(float x, float y, float width, float height) = 0;

        virtual void restoreClipRect() = 0;
    };
}