#pragma once

#include "core/string/String.h"

#include <d3dcommon.h>

namespace Ghurund::Engine::DirectX {
	using namespace Ghurund::Core;

	struct BufferConstantField {
		D3D_SHADER_VARIABLE_CLASS variableClass;
		D3D_SHADER_VARIABLE_TYPE variableType;
		AString name;
		size_t size, offset;
		const void* defaultValue;

		BufferConstantField(
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

		BufferConstantField(const BufferConstantField& other):
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

		BufferConstantField(BufferConstantField&& other):
			variableClass(other.variableClass),
			variableType(other.variableType),
			name(other.name),
			size(other.size),
			offset(other.offset),
			defaultValue(other.defaultValue) {
			other.defaultValue = nullptr;
		}

		~BufferConstantField() {
			delete defaultValue;
		}
	};
}