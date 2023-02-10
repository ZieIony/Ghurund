#pragma once

#include "DocumentElement.h"

namespace Ghurund::UI {
	class TextDocument {
	private:
		DocumentElement* root;

	public:
		TextDocument(const WString& text) :root(ghnew TextElement(text)) {}
	};
}

namespace Ghurund::Core {
	template<>
	const Type& getType<Ghurund::UI::TextDocument>();
}