#pragma once

#include "core/logging/Logger.h"
#include "core/math/Rect.h"

#include "core/Color.h"
#include "ui/Canvas.h"
#include "entity/camera/Camera.h"

#include <wrl.h>
#include <DirectXMath.h>

namespace Ghurund::UI::DirectX {
    using Microsoft::WRL::ComPtr;
    using namespace ::DirectX;
    using namespace Ghurund::Core;
    using namespace Ghurund::Engine;

    class DxCanvas:public ICanvas {
    private:
        Ghurund::Core::Color color;
        List<XMFLOAT4X4> matrixStack;
        IntrusivePointer<Camera> camera = makeIntrusive<Camera>();

    public:
        void init(const IntSize& size) {
            camera->Perspective = false;
            camera->ScreenSize = size;
        }

        virtual bool isAntialiasingEnabled() override {
            return true;
        }

        virtual void setAntialiasingEnabled(bool enabled) override {
        }

        virtual void beginPaint() override {
            XMFLOAT4X4 identity;
            XMStoreFloat4x4(&identity, XMMatrixIdentity());
            matrixStack.add(identity);
            //deviceContext->SetTransform(matrixStack[matrixStack.Size - 1]);
        }

        virtual void endPaint() override;

        virtual void clear(int32_t color) override {
        }

        virtual void setColor(const Ghurund::UI::Color& color) {
            //fillBrush->SetColor(D2D1::ColorF(color));
            //fillBrush->SetOpacity(color.A);
        }

        virtual void drawRect(float x, float y, float width, float height, float thickness, IStrokeStyle* strokeStyle = nullptr) override;

        virtual void fillRect(float x, float y, float width, float height) override;

        virtual void drawShape(Ghurund::UI::Shape& shape, float thickness) override;

        virtual void drawLine(float x1, float y1, float x2, float y2, float thickness, IStrokeStyle* strokeStyle = nullptr) override;

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& src, float alpha = 1.0f) override;

        virtual void drawImage(Ghurund::UI::Bitmap& bitmapImage, const FloatRect& src, const Ghurund::UI::Color& color, float alpha = 1.0f) override;

        virtual void drawImage(VectorImage& svgDocument) override;

        virtual void drawText(Ghurund::UI::TextLayout& layout, float x, float y) override {
            //fillBrush->SetColor(D2D1::ColorF(((TextLayout&)layout).Color));
            //fillBrush->SetOpacity(((TextLayout&)layout).Color.A);
            //deviceContext->DrawRectangle();
            //deviceContext->DrawTextLayout(D2D1::Point2F(x, y), ((TextLayout&)layout).get(), fillBrush.Get());
        }

        virtual void translate(float x, float y) override;

        virtual void scale(float sx, float sy) override;

        virtual void save() override;

        virtual void restore() override;

        virtual void clipShape(Ghurund::UI::Shape& shape) override;

        virtual void restoreClipShape() override;

        virtual void clipRect(float x, float y, float width, float height) override;

        virtual void restoreClipRect() override;
    };
}