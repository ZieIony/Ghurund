#pragma once

#include "core/enum/Enum.h"

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	enum class CompilationTargetEnum {
		SHADER_4_0_LEVEL_9_1, SHADER_4_0_LEVEL_9_3, SHADER_4_0, SHADER_4_1,
		SHADER_5_0,
		SHADER_6_0, SHADER_6_1,SHADER_6_2, SHADER_6_3, SHADER_6_4, SHADER_6_5, SHADER_6_6
	};

	class CompilationTarget:public Enum<CompilationTargetEnum, CompilationTarget> {
	private:
		const AString targetName;

		CompilationTarget(CompilationTargetEnum value, const AString& name, const AString& targetName):
			Enum(value, name), targetName(targetName) {}

	public:
		static const CompilationTarget SHADER_4_0_LEVEL_9_1, SHADER_4_0_LEVEL_9_3, SHADER_4_0, SHADER_4_1,
			SHADER_5_0,
			SHADER_6_0, SHADER_6_1, SHADER_6_2, SHADER_6_3, SHADER_6_4, SHADER_6_5, SHADER_6_6;

		const AString& getTargetName() const {
			return targetName;
		}

		__declspec(property(get = getTargetName)) const AString& TargetName;
	};
}
