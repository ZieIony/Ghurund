#include "ghepch.h"
#include "ShaderSource.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Engine {
	const Ghurund::Core::Type& ShaderSource::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<ShaderSource>();
		return TYPE;
	}
}
