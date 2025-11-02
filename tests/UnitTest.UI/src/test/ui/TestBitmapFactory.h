#pragma once

#include "ui/image/BitmapFactory.h"

namespace UnitTest {
	using namespace Ghurund::UI;

	class TestBitmapFactory:public IBitmapFactory {
	public:
		virtual Ghurund::UI::Bitmap* makeBitmap(Image& image) const override {
			return nullptr;
		}
	};
}