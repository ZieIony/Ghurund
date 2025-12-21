#include "ghuipch.h"
#include "KerningPairs.h"

#include "core/exception/Exceptions.h"
#include "core/logging/Logger.h"

namespace Ghurund::UI {
	void KerningPairs::init(HDC hdc) {
		kerning.clear();
		DWORD result = GetKerningPairs(hdc, -1, nullptr);
		if (result == GDI_ERROR) {
			auto errorCode = GetLastError();
			throw InvalidParamException();
		} else if (result == 0) {
			Logger::log(LogType::INFO, _T("No kerning info for this font.\n"));
			return;
		}
		Array<KERNINGPAIR> kerningPairs(result);
		result = GetKerningPairs(hdc, (DWORD)kerningPairs.Size, &kerningPairs[0]);
		if (result == GDI_ERROR) {
			auto errorCode = GetLastError();
			throw InvalidParamException();
		}
		for (auto& kerningPair : kerningPairs)
			add(kerningPair.wFirst, kerningPair.wSecond, kerningPair.iKernAmount);
	}
	
	void KerningPairs::add(tchar first, tchar second, int16_t value) {
		auto it = kerning.find(first);
		if (it == kerning.end()) {
			Map<tchar, int16_t> map;
			map.put(second, value);
			kerning.put(first, map);
		} else {
			it->value.put(second, value);
		}
	}
}