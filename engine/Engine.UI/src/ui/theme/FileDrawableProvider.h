#pragma once

#include "DrawableProvider.h"
#include "ui/drawable/Drawable.h"
#include "ui/loading/DrawableFactory.h"

namespace Ghurund::UI {
	class FileDrawableProvider:public DrawableProvider {
	private:
		DrawableFactory& drawableFactory;
		ResourcePath resourcePath;
		SharedPointer<Drawable> cached;

	public:
		FileDrawableProvider(
			DrawableFactory& drawableFactory,
			const ResourcePath& resourcePath
		): drawableFactory(drawableFactory), resourcePath(resourcePath) {}

		virtual SharedPointer<Drawable> get() override {
			if (cached == nullptr)
				return SharedPointer<Drawable>((Drawable*)cached->clone());
			cached = SharedPointer<Drawable>(drawableFactory.makeDrawable(resourcePath));
			return cached;
		}
	};
}