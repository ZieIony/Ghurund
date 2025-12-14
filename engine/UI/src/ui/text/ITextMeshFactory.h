#pragma once

#include "CharacterInfo.h"
#include "TextSpan.h"

#include "core/collection/List.h"
#include "core/object/Noncopyable.h"
#include "core/resource/Resource.h"

namespace Ghurund::UI {
	class ITextMeshFactory:public Noncopyable {
	public:
		virtual Resource* makeMesh(const List<CharacterInfo>& characters, const TextSpan& span) const = 0;
	};
}