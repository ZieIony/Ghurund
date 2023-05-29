#pragma once

#include "DocumentElement.h"

namespace Ghurund::UI {
	class TextDocument {
	private:
		DocumentElement* root;

	public:
		TextDocument(const WString& text) :root(ghnew TextElement(text)) {}

		inline size_t getLength() const {
			return root->getLength();
		}

		__declspec(property(get = getLength)) size_t Length;
	};
}

namespace Ghurund::Core {
	template<>
	const Type& getType<Ghurund::UI::TextDocument>();
}