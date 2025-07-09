#pragma once

#include "ui/image/BitmapFactory.h"
#include "ui/direct2d/image/Bitmap.h"

namespace Ghurund::UI::Direct2D {
	class BitmapFactory:public IBitmapFactory {
	private:
		// borrowed
		ID2D1DeviceContext5* deviceContext;

	public:
		BitmapFactory(NotNull<ID2D1DeviceContext5> deviceContext):deviceContext(&deviceContext) {}
	
		virtual Ghurund::UI::Bitmap* makeBitmap(Image& image) const override {
			IntrusivePointer<Bitmap> bitmap(ghnew Bitmap());
			bitmap->init(deviceContext, image);
			bitmap->addReference();
			return bitmap.get();
		}
	};
}