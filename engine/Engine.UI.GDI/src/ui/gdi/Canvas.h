#pragma once

#include "ui/Canvas.h"
#include "core/math/Rect.h"
#include "core/collection/Stack.h"
#include "StrokeStyle.h"
#include "core/Exceptions.h"

#undef GDIPVER
#define GDIPVER     0x0110

#include <gdiplus.h>
#include <uxtheme.h>

#pragma comment (lib, "UxTheme.lib")

namespace Ghurund::UI::GDI {
    using namespace Ghurund::Core;

    class Canvas:public ICanvas {
    private:
        HDC hdc = {};
        PAINTSTRUCT ps = {};
        HWND hwnd = {};
        Gdiplus::Bitmap* bitmap = nullptr;
        HPAINTBUFFER hbuff;
        Gdiplus::Graphics* graphics = nullptr;
        Gdiplus::Color color;
        Gdiplus::GraphicsPath path;
        Gdiplus::Pen* pen = nullptr;
        Gdiplus::SolidBrush* brush = nullptr;
        Stack<Gdiplus::GraphicsState> states;
        Gdiplus::ColorMatrixEffect* colorMatrixEffect;
        Gdiplus::ColorMatrix colorMatrix;
        Gdiplus::Matrix* matrix;

    public:
        ~Canvas() {
            uninit();
        }

        Status init(HWND hwnd);

        void uninit();

        virtual bool isAntialiasingEnabled() override {
            return graphics->GetSmoothingMode() == Gdiplus::SmoothingMode::SmoothingModeAntiAlias;
        }

        virtual void setAntialiasingEnabled(bool enabled) override {
            graphics->SetSmoothingMode(enabled ? Gdiplus::SmoothingMode::SmoothingModeAntiAlias : Gdiplus::SmoothingMode::SmoothingModeNone);
            graphics->SetTextRenderingHint(enabled ? Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias : Gdiplus::TextRenderingHint::TextRenderingHintSystemDefault);
        }

        virtual void beginPaint() override;

        virtual void endPaint() override;

        virtual void clear(int32_t color) override {
            this->color.SetValue(color);
            graphics->Clear(this->color);
        }

        virtual void setColor(const Ghurund::Core::Color& color) {
            this->color.SetValue(color);
        }

        virtual void drawRect(float x, float y, float width, float height, float thickness, IStrokeStyle* strokeStyle = nullptr) override;

        virtual void fillRect(float x, float y, float width, float height) override;

        virtual void drawShape(Ghurund::UI::Shape& shape, float thickness) override;

        virtual void drawLine(float x1, float y1, float x2, float y2, float thickness, IStrokeStyle* strokeStyle = nullptr) override;

        virtual void drawImage(Bitmap& bitmapImage, const FloatRect& dst, float alpha = 1.0f) override;

        virtual void drawImage(Bitmap& bitmapImage, const FloatRect& dst, const Ghurund::Core::Color& tint, float alpha = 1.0f) override;

        virtual void drawImage(Bitmap& bitmapImage, const FloatRect& src, const FloatRect& dst, float alpha = 1.0f) override;

        virtual void drawImage(Bitmap& bitmapImage, const FloatRect& src, const FloatRect& dst, const Ghurund::Core::Color& tint, float alpha = 1.0f) override;

        virtual void drawImage(VectorImage& svgDocument) override;

        virtual void drawText(TextLayout& layout, float x, float y) override {
            throw NotImplementedException();
        }

        virtual void translate(float x, float y) override {
            graphics->TranslateTransform(x, y);
        }

        virtual void save() override {
            states.push(graphics->Save());
        }

        virtual void restore() override {
            Gdiplus::GraphicsState state = states.pop();
            graphics->Restore(state);
        }

        virtual void clipShape(Ghurund::UI::Shape& shape) override {
            //graphics->SetClip(shape.Path, Gdiplus::CombineModeIntersect);
            throw NotImplementedException();
        }

        virtual void restoreClipShape() override {
            throw NotImplementedException();
        }

        virtual void clipRect(float x, float y, float width, float height) override {
            Gdiplus::GraphicsPath path;
            path.AddRectangle(Gdiplus::RectF(x - 0.5f, y - 0.5f, width, height));
            graphics->SetClip(&path, Gdiplus::CombineModeIntersect);
        }

        virtual void restoreClipRect() override {
            throw NotImplementedException();
        }
    };
}

//https://github.com/ZieIony/Ghurund/commit/793824539eb4cfeeb9dab558b59a868a02e327c1