#pragma once

#include "ui/Canvas.h"
#include "core/math/Rect.h"
#include "core/Exceptions.h"

namespace Ghurund::UI::OpenGL {
    using namespace Ghurund::Core;

    class OglCanvas:public ICanvas {
    public:
        virtual bool isAntialiasingEnabled() override {
            return false;
        }

        virtual void setAntialiasingEnabled(bool enabled) override {
            throw NotImplementedException();
        }

        virtual void beginPaint() override {
            throw NotImplementedException();
        }

        virtual void endPaint() override {
            throw NotImplementedException();
        }

        /*virtual void clear(int32_t color) override {
            throw NotImplementedException();
        }*/

        virtual void setColor(const Ghurund::UI::Color& color) override {
            throw NotImplementedException();
        }

        __declspec(property(put = setColor)) Ghurund::UI::Color Color;

        virtual void drawRect(float x, float y, float width, float height, float thickness, IStrokeStyle* strokeStyle = nullptr) override {
            throw NotImplementedException();
        }

        virtual void fillRect(float x, float y, float width, float height) override {
            throw NotImplementedException();
        }

        virtual void drawShape(Ghurund::UI::Shape& shape, float thickness) override {
            throw NotImplementedException();
        }

        virtual void drawLine(float x1, float y1, float x2, float y2, float thickness, IStrokeStyle* strokeStyle = nullptr) override {
            throw NotImplementedException();
        }

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& src, float alpha = 1.0f) override {
            throw NotImplementedException();
        }

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& src, const Ghurund::UI::Color& color, float alpha = 1.0f) override {
            throw NotImplementedException();
        }

        virtual void drawImage(VectorImage& svgDocument) override {
            throw NotImplementedException();
        }

        virtual void drawText(Ghurund::UI::TextLayout& layout, float x, float y) override {
            //fillBrush->SetColor(D2D1::ColorF(((TextLayout&)layout).Color));
            //fillBrush->SetOpacity(((TextLayout&)layout).Color.A);
            //deviceContext->DrawRectangle();
            //deviceContext->DrawTextLayout(D2D1::Point2F(x, y), ((TextLayout&)layout).get(), fillBrush.Get());
            throw NotImplementedException();
        }

        virtual void translate(float x, float y) override {
            throw NotImplementedException();
        }

        virtual void scale(float sx, float sy) override {
            throw NotImplementedException();
        }

        virtual void save() override {
            throw NotImplementedException();
        }

        virtual void restore() override {
            throw NotImplementedException();
        }

        virtual void clipShape(Ghurund::UI::Shape& shape) override {
            throw NotImplementedException();
        }

        virtual void restoreClipShape() override {
            throw NotImplementedException();
        }

        virtual void clipRect(float x, float y, float width, float height) override {
            throw NotImplementedException();
        }

        virtual void restoreClipRect() override {
            throw NotImplementedException();
        }
    };
}
