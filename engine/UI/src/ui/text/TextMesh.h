#pragma once

#include "CharacterInfo.h"
#include "TextSpan.h"

#include "engine/graphics/mesh/MeshData.h"

namespace Ghurund::UI {
	class TextMesh: public Ghurund::Engine::MeshData {
	public:
		void init(const List<CharacterInfo>& characters, const TextSpan& span);
	};
}