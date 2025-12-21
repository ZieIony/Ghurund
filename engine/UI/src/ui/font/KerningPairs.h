#pragma once

#include "Common.h"

#include "core/collection/Map.h"

#include <cstdint>
#include <Windows.h>

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class KerningPairs {
	public:
		Map<tchar, Map<tchar, int16_t>> kerning;
	
		void init(HDC hdc);

		void add(tchar first, tchar second, int16_t value);

		inline int16_t get(tchar c1, tchar c2) const {
			auto it = kerning.find(c1);
			if (it != kerning.end()) {
				auto it2 = it->value.find(c2);
				if (it2 != it->value.end())
					return it2->value;
			}
			return 0;
		}
	};
}