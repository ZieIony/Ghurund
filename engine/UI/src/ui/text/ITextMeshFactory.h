#pragma once

#include "CharacterInfo.h"
#include "TextSpan.h"

#include "core/collection/List.h"
#include "core/object/Noncopyable.h"
#include "engine/graphics/mesh/Mesh.h"

namespace Ghurund::UI {
	using namespace Ghurund::Engine;

	class ITextMeshFactory:public Noncopyable {
	public:
		virtual Mesh* makeMesh(const List<CharacterInfo>& characters, const TextSpan& span) const = 0;
	};
}