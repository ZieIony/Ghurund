#include "ghepch.h"
#include "ShaderInputSemantic.h"

namespace Ghurund::Engine {
	const ShaderInputSemantic ShaderInputSemantic::POSITION = ShaderInputSemantic(ShaderInputSemanticEnum::POSITION, "POSITION");
	const ShaderInputSemantic ShaderInputSemantic::NORMAL = ShaderInputSemantic(ShaderInputSemanticEnum::NORMAL, "NORMAL");
	const ShaderInputSemantic ShaderInputSemantic::TEXCOORD = ShaderInputSemantic(ShaderInputSemanticEnum::TEXCOORD, "TEXCOORD");
	const ShaderInputSemantic ShaderInputSemantic::TANGENT = ShaderInputSemantic(ShaderInputSemanticEnum::TANGENT, "TANGENT");
	const ShaderInputSemantic ShaderInputSemantic::COLOR = ShaderInputSemantic(ShaderInputSemanticEnum::COLOR, "COLOR");
	const ShaderInputSemantic ShaderInputSemantic::OBJECT_ID = ShaderInputSemantic(ShaderInputSemanticEnum::OBJECT_ID, "OBJECT_ID");
}
