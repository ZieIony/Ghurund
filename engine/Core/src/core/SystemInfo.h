#pragma once

#include "core/string/String.h"

#include <cstdint>

namespace Ghurund::Core {
	struct ProcessorInfo {
		uint16_t cores, logicalProcessors;
		AString architecture;
	};

	struct MemoryInfo {
		uint64_t totalKb;
		size_t file, paged, nonPaged, workingSet;
	};

	class SystemInfo {
	private:
		SystemInfo() = delete;

		template<typename Type>
		static inline uint8_t countSetBits(Type n) {
			unsigned int count = 0;
			while (n) {
				n &= (n - 1);
				count++;
			}
			return count;
		}

		static AString getProcessorArchitecture();

	public:
		static ProcessorInfo getProcessorInfo();

		static MemoryInfo getMemoryInfo();
	};
}
