#pragma once

#include "ui/image/BitmapFactory.h"
#include "ui/directx/image/DxBitmap.h"

namespace Ghurund::UI::DirectX {
	class BitmapFactory:public IBitmapFactory {
	public:
		virtual Ghurund::UI::Bitmap* makeBitmap(Image& image) const override {
			IntrusivePointer<DxBitmap> bitmap(ghnew DxBitmap());
			bitmap->init(image);
			bitmap->addReference();
			return bitmap.get();
		}
	};
}