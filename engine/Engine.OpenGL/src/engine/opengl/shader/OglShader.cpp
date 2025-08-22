#include "gheoglpch.h"
#include "OglShader.h"

namespace Ghurund::Engine::OpenGL {
	const Ghurund::Core::Type& OglShader::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<OglShader>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}