#pragma once

#include "core/Object.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
	class Style;

	class StyleAttr: public Ghurund::Core::Object {
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = StyleAttr::GET_TYPE();

		virtual const Style* resolve(const Theme& theme) const = 0;
	};

	class StyleValue: public StyleAttr {
	private:
		const Style* style;

	public:
		StyleValue(const Style* style):style(style) {}

		StyleValue(const StyleValue& other):style(other.style) {}

		StyleValue(StyleValue&& other) noexcept:style(std::move(other.style)) {}

		virtual const Style* resolve(const Theme& theme) const override {
			return style;
		}

		StyleValue& operator=(const StyleValue& other) {
			style = other.style;
			return *this;
		}

		StyleValue& operator=(StyleValue&& other) noexcept {
			if (this == &other)
				return *this;
			style = std::move(other.style);
			return *this;
		}

		virtual StyleValue* clone() const override {
			return ghnew StyleValue(style);
		}
	};

	class StyleRef: public StyleAttr {
	private:
		StyleKey key;

	public:
		StyleRef(StyleKey key):key(key) {}

		virtual const Style* resolve(const Theme& theme) const override;

		virtual StyleRef* clone() const override {
			return ghnew StyleRef(key);
		}
	};
}
