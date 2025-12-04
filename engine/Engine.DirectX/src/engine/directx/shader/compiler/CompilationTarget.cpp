#include "ghedxpch.h"
#include "CompilationTarget.h"

namespace Ghurund::Engine::DirectX {
	const CompilationTarget CompilationTarget::SHADER_5_0 = CompilationTarget(
		CompilationTargetEnum::SHADER_5_0,
		"SHADER_5_0",
		"5_0"
	);
	
	const CompilationTarget CompilationTarget::SHADER_4_1 = CompilationTarget(
		CompilationTargetEnum::SHADER_4_1,
		"SHADER_4_1",
		"4_1"
	);
	
	const CompilationTarget CompilationTarget::SHADER_4_0 = CompilationTarget(
		CompilationTargetEnum::SHADER_4_0,
		"SHADER_4_0",
		"4_0"
	);

	const CompilationTarget CompilationTarget::SHADER_4_0_LEVEL_9_3 = CompilationTarget(
		CompilationTargetEnum::SHADER_4_0_LEVEL_9_3,
		"SHADER_4_0_LEVEL_9_3",
		"4_0_level_9_3"
	);

	const CompilationTarget CompilationTarget::SHADER_4_0_LEVEL_9_1 = CompilationTarget(
		CompilationTargetEnum::SHADER_4_0_LEVEL_9_1,
		"SHADER_4_0_LEVEL_9_1",
		"4_0_level_9_1"
	);
}