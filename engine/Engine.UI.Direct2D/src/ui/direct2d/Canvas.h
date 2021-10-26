#pragma once

#include "ui/Canvas.h"
#include "core/math/Rect.h"
#include "StrokeStyle.h"
#include "ui/direct2d/Shape.h"
#include "ui/direct2d/text/TextLayout.h"

#include <dxgi1_6.h>
#include <d2d1_3.h>
#include <dwrite.h>
#include <d3d11on12.h>
#include <wrl.h>

namespace Ghurund::UI::Direct2D {
    using Microsoft::WRL::ComPtr;
    using namespace Ghurund::Core;

    class Canvas:public ICanvas {
    private:
        ComPtr<ID2D1SolidColorBrush> fillBrush;
        ComPtr<ID2D1SolidColorBrush> strokeBrush;
        List<D2D1::Matrix3x2F> matrixStack;
        ID2D1DeviceContext5* deviceContext = nullptr;
        ComPtr<ID2D1Effect> tintEffect;
        ComPtr<ID2D1Effect> floodEffect;

    public:
        Status init(ID2D1DeviceContext5& deviceContext);

        void uninit();

        virtual bool isAntialiasingEnabled() override {
            return deviceContext->GetAntialiasMode() == D2D1_ANTIALIAS_MODE_PER_PRIMITIVE;
        }

        virtual void setAntialiasingEnabled(bool enabled) override {
            deviceContext->SetAntialiasMode(enabled ? D2D1_ANTIALIAS_MODE_PER_PRIMITIVE : D2D1_ANTIALIAS_MODE_ALIASED);
        }

        virtual void beginPaint() override {
            matrixStack.add(D2D1::Matrix3x2F::Identity());
            deviceContext->SetTransform(matrixStack[matrixStack.Size - 1]);
        }

        virtual void endPaint() override;

        virtual void clear(int32_t color) override {
            deviceContext->Clear(D2D1::ColorF(color));
        }

        virtual void drawRect(float x, float y, float width, float height, const Color& color, float thickness, IStrokeStyle* strokeStyle = nullptr) override {
            fillBrush->SetColor(D2D1::ColorF(color));
            fillBrush->SetOpacity(color.A);
            deviceContext->DrawRectangle(D2D1::RectF(x, y, x + width, y + height), fillBrush.Get(), thickness, strokeStyle ? ((Direct2D::StrokeStyle*)strokeStyle)->get() : nullptr);
        }

        virtual void fillRect(float x, float y, float width, float height, const Color& color) override {
            fillBrush->SetColor(D2D1::ColorF(color));
            fillBrush->SetOpacity(color.A);
            deviceContext->FillRectangle(D2D1::RectF(x, y, x + width, y + height), fillBrush.Get());
        }

        virtual void drawShape(Ghurund::UI::Shape& shape, const Color& color, float thickness) override {
            fillBrush->SetColor(D2D1::ColorF(color));
            fillBrush->SetOpacity(color.A);
            deviceContext->DrawGeometry(((Direct2D::Shape&)shape).Path, fillBrush.Get(), thickness);
        }

        virtual void drawLine(float x1, float y1, float x2, float y2, const Color& color, float thickness, IStrokeStyle* strokeStyle = nullptr) override {
            fillBrush->SetColor(D2D1::ColorF(color));
            fillBrush->SetOpacity(color.A);
            deviceContext->DrawLine({ x1,y1 }, { x2,y2 }, fillBrush.Get(), thickness, strokeStyle ? ((Direct2D::StrokeStyle*)strokeStyle)->get() : nullptr);
        }

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& dst, float alpha = 1.0f) override;

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& dst, const Color& color, float alpha = 1.0f) override;

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& src, const FloatRect& dst, float alpha = 1.0f) override;

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& src, const FloatRect& dst, const Color& color, float alpha = 1.0f) override;

        virtual void drawImage(VectorImage& svgDocument) override;

        virtual void drawText(ITextLayout& layout, float x, float y) override {
            fillBrush->SetColor(D2D1::ColorF(((TextLayout&)layout).Color));
            fillBrush->SetOpacity(((TextLayout&)layout).Color.A);
            deviceContext->DrawTextLayout(D2D1::Point2F(x, y), ((TextLayout&)layout).get(), fillBrush.Get());
        }

        virtual void translate(float x, float y) override {
            matrixStack[matrixStack.Size - 1] = matrixStack[matrixStack.Size - 1] * D2D1::Matrix3x2F::Translation(x, y);
            deviceContext->SetTransform(matrixStack[matrixStack.Size - 1]);
        }

        virtual void save() override {
            matrixStack.add(matrixStack[matrixStack.Size - 1]);
        }

        virtual void restore() override {
            matrixStack.removeAt(matrixStack.Size - 1);
            deviceContext->SetTransform(matrixStack[matrixStack.Size - 1]);
        }

        virtual void clipShape(Ghurund::UI::Shape& shape) override {
            ComPtr<ID2D1Layer> pLayer;
            D2D_SIZE_F size = { shape.Bounds.right - shape.Bounds.left, shape.Bounds.bottom - shape.Bounds.top };
            deviceContext->CreateLayer(&size, &pLayer);
            D2D_RECT_F bounds = D2D_RECT_F{ shape.Bounds.left, shape.Bounds.top, shape.Bounds.right, shape.Bounds.bottom };
            deviceContext->PushLayer(D2D1::LayerParameters(bounds, ((Direct2D::Shape&)shape).Path), pLayer.Get());
        }

        virtual void restoreClipShape() override {
            deviceContext->PopLayer();
        }

        virtual void clipRect(float x, float y, float width, float height) override {
            deviceContext->PushAxisAlignedClip(D2D1::RectF(x, y, x + width, y + height), D2D1_ANTIALIAS_MODE_PER_PRIMITIVE);
        }

        virtual void restoreClipRect() override {
            deviceContext->PopAxisAlignedClip();
        }
    };
}