#pragma once

#include "core/string/String.h"

#pragma warning(push, 0)
#include <d3d12.h>
#pragma warning(pop)

namespace Ghurund::Engine::DirectX {
	using namespace DirectX;

	class ShaderConstant {
	protected:
		AString name;
		uint32_t bindPoint, bindSlot = 0;
		D3D12_SHADER_VISIBILITY visibility;

	public:
		ShaderConstant(
			const AString& name,
			uint32_t bindPoint,
			D3D12_SHADER_VISIBILITY visibility
		):name(name), bindPoint(bindPoint), visibility(visibility) {
		}

		inline const AString& getName() {
			return name;
		}

		__declspec(property(get = getName)) const AString& Name;

		inline uint32_t getBindPoint() const {
			return bindPoint;
		}

		inline uint32_t getBindSlot() const {
			return bindSlot;
		}

		inline void setBindSlot(uint32_t slot) {
			bindSlot = slot;
		}

		__declspec(property(get = getBindSlot, put = setBindSlot)) uint32_t BindSlot;

		inline D3D12_SHADER_VISIBILITY getVisibility() const {
			return visibility;
		}

		inline void setVisibility(D3D12_SHADER_VISIBILITY visibility) {
			this->visibility = visibility;
		}

		__declspec(property(get = getVisibility, put = setVisibility)) D3D12_SHADER_VISIBILITY Visibility;

	};
}