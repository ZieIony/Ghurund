#pragma once

#include "ui/image/BitmapFactory.h"
#include "ui/directx/image/Bitmap.h"

namespace Ghurund::UI::DirectX {
	class BitmapFactory:public IBitmapFactory {
	public:
		virtual Ghurund::UI::Bitmap* makeBitmap(Image& image) const override {
			IntrusivePointer<Bitmap> bitmap(ghnew Bitmap());
			bitmap->init(image);
			bitmap->addReference();
			return bitmap.get();
		}
	};
}