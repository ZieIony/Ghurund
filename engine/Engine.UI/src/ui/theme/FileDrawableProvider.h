#pragma once

#include "DrawableProvider.h"
#include "ui/drawable/Drawable.h"
#include "ui/loading/DrawableFactory.h"

namespace Ghurund::UI {
	class FileDrawableProvider:public DrawableProvider {
	private:
		DrawableFactory& drawableFactory;
		FilePath filePath;
		Drawable* cached = nullptr;

	public:
		FileDrawableProvider(
			DrawableFactory& drawableFactory,
			const FilePath& filePath
		): drawableFactory(drawableFactory), filePath(filePath) {}

		~FileDrawableProvider() {
			if (cached)
				cached->release();
		}

		virtual Drawable* get() override {
			if (cached)
				return (Drawable*)cached->clone();
			cached = drawableFactory.makeDrawable(filePath);
			return cached;
		}
	};
}