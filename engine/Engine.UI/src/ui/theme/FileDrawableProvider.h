#pragma once

#include "DrawableProvider.h"
#include "ui/drawable/Drawable.h"
#include "ui/loading/DrawableFactory.h"

namespace Ghurund::UI {
	class FileDrawableProvider:public DrawableProvider {
	private:
		DrawableFactory& drawableFactory;
		ResourcePath resourcePath;
		IntrusivePointer<Drawable> cached;

	public:
		FileDrawableProvider(
			DrawableFactory& drawableFactory,
			const ResourcePath& resourcePath
		): drawableFactory(drawableFactory), resourcePath(resourcePath) {}

		virtual IntrusivePointer<Drawable> get() override {
			if (cached != nullptr)
				return IntrusivePointer<Drawable>((Drawable*)cached->clone());
			cached = IntrusivePointer<Drawable>(drawableFactory.makeDrawable(resourcePath));
			return cached;
		}
	};
}