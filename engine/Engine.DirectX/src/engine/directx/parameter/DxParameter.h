#pragma once

#include "engine/parameter/ParameterManager.h"
#include "engine/parameter/ValueParameter.h"

#include <d3dcompiler.h>

namespace Ghurund::Engine::DirectX {
	using namespace ::DirectX;
	using namespace Ghurund::Core;

	template<typename T>
	Parameter* makeDxParameter(
		const AString& name,
		void* defaultValue
	) {
		auto vp = ghnew T(name);
		if (defaultValue)
			vp->Value = *(typename T::value_t*)defaultValue;
		return vp;
	}

	Parameter* makeDxParameterByType(
		D3D_SHADER_VARIABLE_CLASS _class,
		D3D_SHADER_VARIABLE_TYPE type,
		const AString& name,
		uint16_t size,
		void* defaultValue
	);
}