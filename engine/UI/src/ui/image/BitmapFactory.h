#pragma once

#include <core/image/Image.h>
#include <ui/image/Bitmap.h>

namespace Ghurund::UI {
	class IBitmapFactory {
	public:
		virtual Ghurund::UI::Bitmap* makeBitmap(Image& image) const = 0;
	};
}