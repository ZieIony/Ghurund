#pragma once

#include "BufferConstantField.h"
#include "ShaderConstant.h"

#include <d3dcompiler.h>

namespace Ghurund::Engine::DirectX {
	class BufferConstant:public ShaderConstant {
	private:
		uint32_t size = 0;
		List<BufferConstantField> fields;

		BufferConstant(const BufferConstant& other) = delete;

	public:
		BufferConstant(
			const AString& name,
			uint32_t bindPoint,
			D3D12_SHADER_VISIBILITY visibility
		);

		void init(ID3D12ShaderReflectionConstantBuffer& constantBuffer, D3D12_SHADER_BUFFER_DESC& bufferDesc);

		inline uint32_t getSize() const {
			return size;
		}

		__declspec(property(get = getSize)) uint32_t Size;

		inline const List<BufferConstantField>& getFields() const {
			return fields;
		}

		__declspec(property(get = getFields)) const List<BufferConstantField>& Fields;
	};
}