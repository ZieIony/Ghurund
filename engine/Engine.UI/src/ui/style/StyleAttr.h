#pragma once

#include "core/Object.h"
#include "Theme.h"

namespace Ghurund::UI {
	class Style;

	class StyleAttr : public Ghurund::Core::Object {
	public:
		virtual const Style* resolve(const Theme& theme) const = 0;
	};

	class StyleValue : public StyleAttr {
	private:
		Style* style;

	public:
		StyleValue(Style* style) :style(style) {}

		virtual const Style* resolve(const Theme& theme) const override {
			return style;
		}

		virtual StyleValue* clone() const override {
			return ghnew StyleValue(style);
		}
	};

	class StyleRef : public StyleAttr {
	private:
		StyleKey key;

	public:
		StyleRef(StyleKey key) :key(key) {}

		virtual const Style* resolve(const Theme& theme) const override;

		virtual StyleRef* clone() const override {
			return ghnew StyleRef(key);
		}
	};
}
