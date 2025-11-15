#pragma once

#include "MeshData.h"
#include <ui/font/Font.h>

namespace Ghurund::Engine {
	class TextMesh: public MeshData {
	public:
		void init(const WString& text, const Ghurund::UI::Font& font);
	};
}