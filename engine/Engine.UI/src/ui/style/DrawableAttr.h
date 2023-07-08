#pragma once

#include "core/Object.h"
#include "Theme.h"
#include "ui/drawable/Drawable.h"

namespace Ghurund::UI {
	class DrawableAttr: public Ghurund::Core::Object {
	public:
		virtual const Drawable* resolve(const Theme& theme) const = 0;
	};

	class DrawableValue: public DrawableAttr {
	private:
		Drawable* drawable = nullptr;

	public:
		DrawableValue(Drawable* drawable):drawable(drawable) {
			if (drawable)
				drawable->addReference();
		}

		DrawableValue(const DrawableValue& other):drawable(other.drawable) {
			if (drawable)
				drawable->addReference();
		}

		DrawableValue(DrawableValue&& other) noexcept:drawable(std::move(other.drawable)) {}

		~DrawableValue() {
			if (drawable)
				drawable->release();
		}

		virtual const Drawable* resolve(const Theme& theme) const override {
			return drawable;
		}

		DrawableValue& operator=(const DrawableValue& other) {
			drawable = other.drawable;
			if (drawable)
				drawable->addReference();
			return *this;
		}

		DrawableValue& operator=(DrawableValue&& other) noexcept {
			if (this == &other)
				return *this;
			drawable = std::move(other.drawable);
			return *this;
		}

		virtual DrawableValue* clone() const override {
			return ghnew DrawableValue(drawable);
		}
	};

	class DrawableRef: public DrawableAttr {
	private:
		DrawableKey key;

	public:
		DrawableRef(DrawableKey key):key(key) {}

		virtual const Drawable* resolve(const Theme& theme) const override;

		virtual DrawableRef* clone() const override {
			return ghnew DrawableRef(key);
		}
	};
}
