#pragma once

#include "core/object/Object.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI {
	class Font;

	class FontAttr: public Ghurund::Core::Object {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = FontAttr::GET_TYPE();
#pragma endregion

	public:
		virtual const Ghurund::UI::Font* resolve(const Theme& theme) const = 0;
	};

	class FontValue: public FontAttr {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = FontValue::GET_TYPE();
#pragma endregion

	private:
		Ghurund::UI::Font* font;

	public:
		FontValue(Ghurund::UI::Font* Font):font(Font) {}

		virtual const Ghurund::UI::Font* resolve(const Theme& theme) const override {
			return font;
		}

		virtual FontValue* clone() const override {
			return ghnew FontValue(font);
		}
	};

	class FontRef: public FontAttr {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = FontRef::GET_TYPE();
#pragma endregion

	private:
		FontKey key;

	public:
		FontRef(FontKey key):key(key) {}

		virtual const Ghurund::UI::Font* resolve(const Theme& theme) const override;

		virtual FontRef* clone() const override {
			return ghnew FontRef(key);
		}
	};
}
