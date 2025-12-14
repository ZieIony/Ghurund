#pragma once

#include "DocumentElement.h"

#include "core/resource/Resource.h"
#include "ui/font/Font.h"

namespace Ghurund::UI {
	class TextDocument:public Resource {
	private:
		//DocumentElement* root;
		WString text;
		const Font* font = nullptr;
		Color color;

	public:
		TextDocument(const WString& text, NotNull<Font> font, Color color):text(text), font(&font), color(color) {
			font->addReference();
		}

		~TextDocument() {
			if (font)
				font->release();
		}

		inline size_t getLength() const {
			return text.Length;
		}

		__declspec(property(get = getLength)) size_t Length;

		inline wchar_t charAt(size_t position) const {
			return text[position];
		}

		inline const Font* getFont(size_t position) const {
			return font;
		}

		inline const Font* getFont() const {
			return font;
		}

		inline void setFont(NotNull<const Font> font) {
			setPointer(this->font, &font);
		}

		__declspec(property(get = getFont, put = setFont)) Font* Font;

		inline const Color& getTextColor(size_t position) const {
			return color;
		}

		inline const Color& getTextColor() const {
			return color;
		}

		inline void setTextColor(const Color& color) {
			this->color = color;
		}

		__declspec(property(get = getTextColor, put = setTextColor)) const Color& TextColor;

		inline void insert(size_t position, const WString& text) {
			this->text.insert(position, text);
		}

		inline void remove(size_t position, size_t length) {
			text.remove(position, length);
		}

		inline bool operator==(const TextDocument& other) const {
			return text == other.text;
		}
	};
}

namespace Ghurund::Core {
	template<>
	const Type& getType<Ghurund::UI::TextDocument>();
}