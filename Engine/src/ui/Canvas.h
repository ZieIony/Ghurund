#pragma once

#include "Color.h"
#include "Paint.h"
#include "Shape.h"
#include "core/math/Rect.h"

#include "Graphics2D.h"

namespace Ghurund {
    class SwapChain;
}

namespace Ghurund::UI {
    using namespace Ghurund;

    class BitmapImage;
    class SvgImage;

    class Canvas {
    private:
        ComPtr<ID2D1SolidColorBrush> fillBrush;
        ComPtr<ID2D1SolidColorBrush> strokeBrush;
        List<D2D1::Matrix3x2F> matrixStack;
        ID2D1DeviceContext5* deviceContext = nullptr;
        Graphics2D* graphics2d;
        ComPtr<ID2D1Effect> tintEffect;
        ComPtr<ID2D1Effect> shadowEffect;
        ComPtr<ID2D1Effect> floodEffect;

    public:
        Status init(Graphics2D& graphics2d);

        inline bool isAntialiasingEnabled() {
            return deviceContext->GetAntialiasMode() == D2D1_ANTIALIAS_MODE_PER_PRIMITIVE;
        }

        inline void setAntialiasingEnabled(bool enabled) {
            deviceContext->SetAntialiasMode(enabled ? D2D1_ANTIALIAS_MODE_PER_PRIMITIVE : D2D1_ANTIALIAS_MODE_ALIASED);
        }

        __declspec(property(get = isAntialiasingEnabled, put = setAntialiasingEnabled)) bool AntialiasingEnabled;

        inline void beginPaint() {
            matrixStack.add(D2D1::Matrix3x2F::Identity());
            deviceContext->SetTransform(matrixStack[matrixStack.Size - 1]);
        }

        void endPaint();

        inline void clear(int32_t color) {
            deviceContext->Clear(D2D1::ColorF(color));
        }

        inline void drawRect(float x, float y, float width, float height, const Paint& paint) {
            uint32_t c = paint.Color;
            fillBrush->SetColor(D2D1::ColorF(paint.Color));
            fillBrush->SetOpacity((paint.Color >> 24) / 255.0f);
            deviceContext->DrawRectangle(D2D1::RectF(x, y, x + width, y + height), fillBrush.Get(), paint.Thickness);
        }

        inline void fillRect(float x, float y, float width, float height, const Paint& paint) {
            fillBrush->SetColor(D2D1::ColorF(paint.Color));
            fillBrush->SetOpacity((paint.Color >> 24) / 255.0f);
            deviceContext->FillRectangle(D2D1::RectF(x, y, x + width, y + height), fillBrush.Get());
        }

        inline void drawShape(Shape& shape, const Paint& paint) {
            fillBrush->SetColor(D2D1::ColorF(paint.Color));
            fillBrush->SetOpacity((paint.Color >> 24) / 255.0f);
            deviceContext->DrawGeometry(shape.Path, fillBrush.Get(), paint.Thickness);
        }

        inline void drawShadow(Shape& shape, const Paint& paint) {
            fillBrush->SetColor(D2D1::ColorF(paint.Color));
            fillBrush->SetOpacity((paint.Color >> 24) / 255.0f);
            deviceContext->DrawGeometry(shape.Path, fillBrush.Get(), paint.Thickness);
        }

        inline void drawLine(float x1, float y1, float x2, float y2, const Paint& paint) {}

        void drawImage(BitmapImage& image, const FloatRect& dst, float alpha = 1.0f);

        void drawImage(BitmapImage& image, const FloatRect& dst, int32_t tintColor, float alpha = 1.0f);

        void drawImage(BitmapImage& image, const FloatRect& src, const FloatRect& dst, float alpha = 1.0f);

        void drawImage(BitmapImage& image, const FloatRect& src, const FloatRect& dst, int32_t tintColor, float alpha = 1.0f);

        void drawImage(SvgImage& image);

        void drawShadow(BitmapImage& image, float radius, int32_t shadowColor);

        inline void drawText(IDWriteTextLayout* layout, float x, float y, const Paint& paint) {
            fillBrush->SetColor(D2D1::ColorF(paint.Color));
            fillBrush->SetOpacity((paint.Color >> 24) / 255.0f);
            deviceContext->DrawTextLayout(D2D1::Point2F(x, y), layout, fillBrush.Get());
        }

        inline void translate(float x, float y) {
            matrixStack[matrixStack.Size - 1] = matrixStack[matrixStack.Size - 1] * D2D1::Matrix3x2F::Translation(x, y);
            deviceContext->SetTransform(matrixStack[matrixStack.Size - 1]);
        }

        inline void transform(const D2D1::Matrix3x2F& matrix) {
            matrixStack[matrixStack.Size - 1] = matrixStack[matrixStack.Size - 1] * matrix;
            deviceContext->SetTransform(matrixStack[matrixStack.Size - 1]);
        }

        inline void save() {
            matrixStack.add(matrixStack[matrixStack.Size - 1]);
        }

        inline void restore() {
            matrixStack.removeAt(matrixStack.Size - 1);
            deviceContext->SetTransform(matrixStack[matrixStack.Size - 1]);
        }

        inline void clipShape(Shape& shape) {
            ComPtr<ID2D1Layer> pLayer;
            D2D_SIZE_F size = { shape.Bounds.right - shape.Bounds.left, shape.Bounds.bottom - shape.Bounds.top };
            deviceContext->CreateLayer(&size, &pLayer);
            deviceContext->PushLayer(D2D1::LayerParameters(D2D_RECT_F{ shape.Bounds.left, shape.Bounds.top, shape.Bounds.right, shape.Bounds.bottom }, shape.Path), pLayer.Get());
        }

        inline void restoreClipShape() {
            deviceContext->PopLayer();
        }

        inline void clipRect(float x, float y, float width, float height) {
            deviceContext->PushAxisAlignedClip(D2D1::RectF(x, y, x + width, y + height), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
        }

        inline void restoreClipRect() {
            deviceContext->PopAxisAlignedClip();
        }
    };
}