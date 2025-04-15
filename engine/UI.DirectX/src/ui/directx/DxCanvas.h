#pragma once

#include "core/math/Rect.h"

#include "core/Color.h"
#include "core/IntrusivePointer.h"
#include "entity/camera/Camera.h"
#include "engine/directx/CommandList.h"
#include "ui/Canvas.h"

#include <DirectXMath.h>

namespace Ghurund::UI::DirectX {
	using Microsoft::WRL::ComPtr;
	using namespace ::DirectX;
	using namespace Ghurund::Core;
	using namespace Ghurund::Engine;
	using namespace Ghurund::Engine::DirectX;

	class DxCanvas:public ICanvas {
	private:
		Ghurund::Core::Color color;
		List<XMFLOAT4X4> matrixStack;
		IntrusivePointer<Camera> camera = makeIntrusive<Camera>();
		CommandList* commandList;
		RenderTarget* renderTarget;

	public:
		void init(const IntSize& size) {
			camera->Perspective = false;
			camera->ScreenSize = size;
		}

		virtual bool isAntialiasingEnabled() override {
			return true;
		}

		virtual void setAntialiasingEnabled(bool enabled) override {
			throw NotImplementedException();
		}

		void setContext(CommandList& commandList, RenderTarget& renderTarget) {
			this->commandList = &commandList;
			this->renderTarget = &renderTarget;
		}

		virtual void beginPaint() override {
			XMFLOAT4X4 identity;
			XMStoreFloat4x4(&identity, XMMatrixIdentity());
			matrixStack.add(identity);
			//deviceContext->SetTransform(matrixStack[matrixStack.Size - 1]);
		}

		virtual void endPaint() override {
			throw NotImplementedException();
		}

		virtual void setColor(const Ghurund::UI::Color& color) {
			//fillBrush->SetColor(D2D1::ColorF(color));
			//fillBrush->SetOpacity(color.A);
		}

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