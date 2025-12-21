#pragma once

#include "DocumentElement.h"

#include "core/resource/Resource.h"
#include "ui/font/TextStyle.h"

namespace Ghurund::UI {
	class TextDocument:public Resource {
	private:
		//DocumentElement* root;
		WString text;
		const TextStyle* textStyle = nullptr;
		Color color;

	public:
		TextDocument(
			const WString& text,
			NotNull<TextStyle> textStyle,
			Color color
		):text(text), textStyle(&textStyle), color(color) {
			textStyle->addReference();
		}

		~TextDocument() {
			if (textStyle)
				textStyle->release();
		}

		inline size_t getLength() const {
			return text.Length;
		}

		__declspec(property(get = getLength)) size_t Length;

		inline wchar_t charAt(size_t position) const {
			return text[position];
		}

		inline const TextStyle* getTextStyle(size_t position) const {
			return textStyle;
		}

		inline const TextStyle* getTextStyle() const {
			return textStyle;
		}

		inline void setTextStyle(NotNull<const TextStyle> textStyle) {
			setPointer(this->textStyle, &textStyle);
		}

		__declspec(property(get = getTextStyle, put = setTextStyle)) TextStyle* TextStyle;

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