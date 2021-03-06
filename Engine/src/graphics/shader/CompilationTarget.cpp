#include "ghpch.h"
#include "CompilationTarget.h"

namespace Ghurund {
	const CompilationTarget &CompilationTarget::SHADER_5_0 = CompilationTarget(0, "5_0");
	const CompilationTarget &CompilationTarget::SHADER_4_1 = CompilationTarget(1, "4_1");
	const CompilationTarget &CompilationTarget::SHADER_4_0 = CompilationTarget(2, "4_0");
	const CompilationTarget &CompilationTarget::SHADER_4_0_LEVEL_9_3 = CompilationTarget(3, "4_0_level_9_3");
	const CompilationTarget &CompilationTarget::SHADER_4_0_LEVEL_9_1 = CompilationTarget(4, "4_0_level_9_1");
}