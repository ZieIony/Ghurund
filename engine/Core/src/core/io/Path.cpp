#include "ghcpch.h"

#include <regex>

namespace Ghurund::Core {
	bool Path::getIsAbsolute() const {
		std::wregex regex(L"lib://.*|.:.*");
		std::wsmatch m;
		std::wstring s = path.Data;
		return std::regex_match(s, m, regex);
	}
}
