#pragma once

#include "core/logging/Logger.h"
#include "core/math/Rect.h"

#include "StrokeStyle.h"
#include "ui/Canvas.h"
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

        virtual void setColor(const Ghurund::UI::Color& color) {
            fillBrush->SetColor(D2D1::ColorF(color));
            fillBrush->SetOpacity(color.A);
        }

        virtual void drawRect(float x, float y, float width, float height, float thickness, IStrokeStyle* strokeStyle = nullptr) override;

        virtual void fillRect(float x, float y, float width, float height) override;

        virtual void drawShape(Ghurund::UI::Shape& shape, float thickness) override;

        virtual void drawLine(float x1, float y1, float x2, float y2, float thickness, IStrokeStyle* strokeStyle = nullptr) override;

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& dst, float alpha = 1.0f) override;

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& dst, const Ghurund::UI::Color& color, float alpha = 1.0f) override;

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& src, const FloatRect& dst, float alpha = 1.0f) override;

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& src, const FloatRect& dst, const Ghurund::UI::Color& color, float alpha = 1.0f) override;

        virtual void drawImage(VectorImage& svgDocument) override;

        virtual void drawText(ITextLayout& layout, float x, float y) override {
            fillBrush->SetColor(D2D1::ColorF(((TextLayout&)layout).Color));
            fillBrush->SetOpacity(((TextLayout&)layout).Color.A);
            //deviceContext->DrawRectangle();
            deviceContext->DrawTextLayout(D2D1::Point2F(x, y), ((TextLayout&)layout).get(), fillBrush.Get());
        }

        virtual void translate(float x, float y) override;

        virtual void save() override;

        virtual void restore() override;

        virtual void clipShape(Ghurund::UI::Shape& shape) override;

        virtual void restoreClipShape() override;

        virtual void clipRect(float x, float y, float width, float height) override;

        virtual void restoreClipRect() override;
    };
}