#pragma once

#include "MeshData.h"
#include <ui/font/Font.h>

namespace Ghurund::Engine {
	class ITextMeshFactory:public Noncopyable {
	public:
		virtual Resource* makeMesh(const WString& text, const Ghurund::UI::Font& font) const = 0;
	};
}