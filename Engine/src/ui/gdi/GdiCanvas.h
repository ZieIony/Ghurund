#pragma once

#include "GdiFont.h"
#include "ui/Canvas.h"
#include "GdiPath.h"

#include <uxtheme.h>

#pragma comment (lib, "UxTheme.lib")

namespace Ghurund::UI {
    class GdiCanvas : public Canvas {
    private:
        PAINTSTRUCT ps = {};
        HWND hwnd = {};
        HPAINTBUFFER hbuff;
        Gdiplus::Graphics* graphics = nullptr;
        Gdiplus::Color color;
        Gdiplus::Pen* pen = nullptr;
        Gdiplus::SolidBrush* brush = nullptr;
        List<Gdiplus::GraphicsState> states;
        Gdiplus::ColorMatrixEffect* colorMatrixEffect;
        Gdiplus::ColorMatrix colorMatrix;
        Gdiplus::Matrix* matrix;

    public:
        GdiCanvas(HWND hwnd) {
            BufferedPaintInit();
            this->hwnd = hwnd;
            pen = new Gdiplus::Pen(Gdiplus::Color());
            brush = new Gdiplus::SolidBrush(Gdiplus::Color());
            colorMatrixEffect = new Gdiplus::ColorMatrixEffect();
            colorMatrix = {
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 0.0f, 0.0f,
                0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
                1.0f, 1.0f, 1.0f, 0.0f, 1.0f
            };
            matrix = new Gdiplus::Matrix();
        }

        virtual ~GdiCanvas() {
            BufferedPaintUnInit();
            delete matrix;
            delete colorMatrixEffect;
            delete pen;
            delete brush;
        }

        void beginPaint() {
            HDC hdc = BeginPaint(hwnd, &ps);
            RECT rc;
            GetClientRect(hwnd, &rc);
            HDC memdc;
            hbuff = BeginBufferedPaint(hdc, &rc, BPBF_COMPATIBLEBITMAP, NULL, &memdc);
            graphics = Gdiplus::Graphics::FromHDC(memdc);
            graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
            graphics->SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);
        }

        void endPaint() {
            EndBufferedPaint(hbuff, TRUE);
            EndPaint(hwnd, &ps);
            delete graphics;
            graphics = nullptr;
        }

        void clear(unsigned int color) {
            this->color.SetValue(color);
            graphics->Clear(this->color);
        }

        void drawRect(float x, float y, float width, float height, const Paint& paint) {
            color.SetValue(paint.Color);
            pen->SetWidth(paint.Thickness);
            pen->SetColor(color);
            graphics->DrawRectangle(pen, Gdiplus::RectF(x, y, width, height));
        }

        void fillRect(float x, float y, float width, float height, const Paint& paint) {
            color.SetValue(paint.Color);
            brush->SetColor(color);
            graphics->FillRectangle(brush, Gdiplus::RectF(x, y, width, height));
        }

        virtual void drawPath(const GdiPath& path, const Paint& paint) {
            color.SetValue(paint.Color);
            pen->SetWidth(paint.Thickness);
            pen->SetColor(color);
            graphics->DrawPath(pen, path.path);
        }

        void drawLine(float x1, float y1, float x2, float y2, const Paint& paint) {
            color.SetValue(paint.Color);
            pen->SetWidth(paint.Thickness);
            pen->SetColor(color);
            Gdiplus::GraphicsPath path;
            path.AddLine(Gdiplus::PointF(x1, y1), Gdiplus::PointF(x2, y2));
            graphics->DrawPath(pen, &path);
        }

        void drawText(const String& text, float x, float y, float width, float height, const Ghurund::UI::Font& font, const Paint& paint) {
            font.drawText(*this, text, x, y, paint.Color);
        }

        void drawImage(Gdiplus::Image& image, float x, float y, float width, float height) {
            graphics->DrawImage(&image, x, y, width, height);
        }

        virtual void drawImage(Gdiplus::Image& image, float x, float y, Gdiplus::RectF src) {
            graphics->DrawImage(&image, x, y, src.X, src.Y, src.Width, src.Height, Gdiplus::Unit::UnitPixel);
        }

        virtual void drawImage(Gdiplus::Image& image, float x, float y, Gdiplus::RectF src, int32_t tintColor);

        void translate(float x, float y) {
            graphics->TranslateTransform(x, y);
        }

        void save() {
            states.add(graphics->Save());
        }

        void restore() {
            Gdiplus::GraphicsState state = states.get(states.Size - 1);
            graphics->Restore(state);
            states.removeAtKeepOrder(states.Size - 1);
        }

        void clipPath(const GdiPath& path) {
            graphics->SetClip(path.path, Gdiplus::CombineModeReplace);
        }

        void clipRect(float x, float y, float width, float height) {
            Gdiplus::GraphicsPath path;
            path.AddRectangle(Gdiplus::RectF(x, y, width, height));
            graphics->SetClip(&path, Gdiplus::CombineModeReplace);
        }
    };
}