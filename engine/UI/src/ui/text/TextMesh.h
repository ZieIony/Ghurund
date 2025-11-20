#pragma once

#include "engine/graphics/mesh/MeshData.h"
#include <ui/font/Font.h>

namespace Ghurund::UI {
	class TextMesh: public Ghurund::Engine::MeshData {
	public:
		void init(const WString& text, const Ghurund::UI::Font& font);
	};
}