#pragma once

#include "core/Object.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
	class TextFormat;

	class TextFormatAttr : public Ghurund::Core::Object {
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = TextFormatAttr::GET_TYPE();

		virtual const TextFormat* resolve(const Theme& theme) const = 0;
	};

	class TextFormatValue : public TextFormatAttr {
	private:
		TextFormat* textFormat;

	public:
		TextFormatValue(TextFormat* TextFormat) :textFormat(TextFormat) {}

		virtual const TextFormat* resolve(const Theme& theme) const override {
			return textFormat;
		}

		virtual TextFormatValue* clone() const override {
			return ghnew TextFormatValue(textFormat);
		}
	};

	class TextFormatRef : public TextFormatAttr {
	private:
		TextFormatKey key;

	public:
		TextFormatRef(TextFormatKey key) :key(key) {}

		virtual const TextFormat* resolve(const Theme& theme) const override;

		virtual TextFormatRef* clone() const override {
			return ghnew TextFormatRef(key);
		}
	};
}
