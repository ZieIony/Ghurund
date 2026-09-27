#pragma once

#include "ConstantBuffer.h"
#include "ValueConstant.h"

#include "core/string/String.h"

#include <memory>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class BufferConstant {
	public:
		const AString name;
		const uint32_t bindSlot;
		const uint32_t size;
		const Array<ValueConstant> valueConstants;

		ConstantBuffer* constantBuffer = nullptr;

		BufferConstant(
			const AString& name,
			uint32_t bindSlot,
			uint32_t size,
			Array<ValueConstant> valueConstants
		):name(name), bindSlot(bindSlot), size(size), valueConstants(valueConstants) {
		}

		BufferConstant(
			const BufferConstant& other
		):name(other.name), bindSlot(other.bindSlot), size(other.size), valueConstants(other.valueConstants) {
		}

		BufferConstant(
			BufferConstant&& other
		) noexcept:name(other.name), bindSlot(other.bindSlot), size(other.size), valueConstants(other.valueConstants) {
		}
	};
}
