#pragma once

#include "core/string/String.h"

#include <d3dcommon.h>

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	struct ConstantBufferField {
		D3D_SHADER_VARIABLE_CLASS variableClass;
		D3D_SHADER_VARIABLE_TYPE variableType;
		AString name;
		size_t size, offset;
		const void* defaultValue;

		ConstantBufferField(
			D3D_SHADER_VARIABLE_CLASS variableClass,
			D3D_SHADER_VARIABLE_TYPE variableType,
			AString name,
			size_t size,
			size_t offset,
			const void* defaultValue
		):variableClass(variableClass), variableType(variableType), name(name), size(size), offset(offset), defaultValue([&]->const void* {
			if (defaultValue) {
				void* copy = ghnew uint8_t[size];
				memcpy(copy, defaultValue, size);
				return copy;
			} else {
				return nullptr;
			}
		}()) {
		}

		ConstantBufferField(const ConstantBufferField& other):
			variableClass(other.variableClass),
			variableType(other.variableType),
			name(other.name),
			size(other.size),
			offset(other.offset),
			defaultValue([&]->const void* {
			if (other.defaultValue) {
				void* copy = ghnew uint8_t[size];
				memcpy(copy, other.defaultValue, size);
				return copy;
			} else {
				return nullptr;
			}
		}()) {
		}

		ConstantBufferField(ConstantBufferField&& other):
			variableClass(other.variableClass),
			variableType(other.variableType),
			name(other.name),
			size(other.size),
			offset(other.offset),
			defaultValue(other.defaultValue) {
			other.defaultValue = nullptr;
		}

		~ConstantBufferField() {
			delete defaultValue;
		}
	};
}