#pragma once

#include "GdiFont.h"
#include "ui/Canvas.h"
#include "GdiPath.h"
#include "GdiImage.h"
#include "ui/DrawingCache.h"

#include <uxtheme.h>

#pragma comment (lib, "UxTheme.lib")

namespace Ghurund::UI {
    class GdiCanvas: public Canvas {
    private:
        HDC hdc = {};
        PAINTSTRUCT ps = {};
        HWND hwnd = {};
        Gdiplus::Bitmap* bitmap = nullptr;
        HPAINTBUFFER hbuff;
        Gdiplus::Graphics* graphics = nullptr;
        Gdiplus::Color color;
        Gdiplus::Pen* pen = nullptr;
        Gdiplus::SolidBrush* brush = nullptr;
        List<Gdiplus::GraphicsState> states;
        Gdiplus::ColorMatrixEffect* colorMatrixEffect;
        Gdiplus::ColorMatrix colorMatrix;
        Gdiplus::Matrix* matrix;

        GdiCanvas() {
            BufferedPaintInit();
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

    public:
        GdiCanvas(HWND hwnd):GdiCanvas() {
            this->hwnd = hwnd;
        }

        GdiCanvas(Gdiplus::Bitmap* bitmap):GdiCanvas() {
            this->bitmap = bitmap;
        }

        virtual ~GdiCanvas() {
            BufferedPaintUnInit();
            delete matrix;
            delete colorMatrixEffect;
            delete pen;
            delete brush;
        }

        void beginPaint() {
            if (bitmap) {
                graphics = Gdiplus::Graphics::FromImage(bitmap);
            }else{
                hdc = GetDC(hwnd);// BeginPaint(hwnd, &ps);
                RECT rc;
                GetClientRect(hwnd, &rc);
                HDC memdc;
                hbuff = BeginBufferedPaint(hdc, &rc, BPBF_COMPATIBLEBITMAP, NULL, &memdc);
                graphics = Gdiplus::Graphics::FromHDC(memdc);
            }
            graphics->SetSmoothingMode(Gdiplus::SmoothingMode::SmoothingModeAntiAlias);
            graphics->SetTextRenderingHint(Gdiplus::TextRenderingHint::TextRenderingHintAntiAlias);
        }

        void endPaint() {
            if (!bitmap) {
                EndBufferedPaint(hbuff, TRUE);
                ReleaseDC(hwnd, hdc);
                //EndPaint(hwnd, &ps);
            }
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
            graphics->DrawRectangle(pen, Gdiplus::RectF(x - 0.5f, y - 0.5f, width, height));
        }

        void fillRect(float x, float y, float width, float height, const Paint& paint) {
            color.SetValue(paint.Color);
            brush->SetColor(color);
            graphics->FillRectangle(brush, Gdiplus::RectF(x - 0.5f, y - 0.5f, width, height));
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
            path.AddLine(Gdiplus::PointF(x1 - 0.5f, y1 - 0.5f), Gdiplus::PointF(x2 - 0.5f, y2 - 0.5f));
            graphics->DrawPath(pen, &path);
        }

        void drawImage(const GdiImage& image, float x, float y, float width, float height) {
            graphics->DrawImage(image.image, x, y, width, height);
        }

        virtual void drawImage(const GdiImage& image, float x, float y, float width, float height, int32_t tintColor);

        virtual void drawImage(const GdiImage& image, Gdiplus::RectF src, Gdiplus::RectF dst);

        virtual void drawImage(const GdiImage& image, Gdiplus::RectF src, Gdiplus::RectF dst, int32_t tintColor);

        void translate(float x, float y) {
            graphics->TranslateTransform(x, y);
        }

        virtual void transform(Gdiplus::Matrix& matrix) {
            graphics->MultiplyTransform(&matrix);
        }

        void save() {
            states.add(graphics->Save());
        }

        void restore() {
            Gdiplus::GraphicsState state = states.get(states.Size - 1);
            graphics->Restore(state);
            states.removeAt(states.Size - 1);
        }

        void clipPath(const GdiPath& path) {
            graphics->SetClip(path.path, Gdiplus::CombineModeIntersect);
        }

        void clipRect(float x, float y, float width, float height) {
            Gdiplus::GraphicsPath path;
            path.AddRectangle(Gdiplus::RectF(x - 0.5f, y - 0.5f, width, height));
            graphics->SetClip(&path, Gdiplus::CombineModeIntersect);
        }

        virtual Canvas* beginCache(unsigned int width, unsigned int height) override {
            Gdiplus::Bitmap* bitmap = new Gdiplus::Bitmap(width, height, graphics);
            Canvas* c = ghnew GdiCanvas(bitmap);
            c->beginPaint();
            return c;
        }

        virtual DrawingCache* endCache() override;

        void drawCachedBitmap(Gdiplus::CachedBitmap* bitmap, unsigned int x, unsigned int y) {
            graphics->DrawCachedBitmap(bitmap, x, y);
        }

    };
}