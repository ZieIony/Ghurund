#pragma once

#include "DocumentElement.h"

namespace Ghurund::UI {
	class TextDocument {
	private:
		//DocumentElement* root;
		WString text;

	public:
		TextDocument(const WString& text):text(text) {}

		inline size_t getLength() const {
			return text.Length;
		}

		__declspec(property(get = getLength)) size_t Length;

		inline wchar_t charAt(uint32_t position) const {
			return text[position];
		}

		inline TextFormat* getTextFormat(uint32_t position) const {
			return nullptr;
		}

		inline void insert(uint32_t position, const WString& text) {
			this->text.insert(position, text);
		}

		inline void remove(uint32_t position, uint32_t length) {
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