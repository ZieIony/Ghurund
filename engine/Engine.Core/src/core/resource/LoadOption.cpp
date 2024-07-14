#include "ghcpch.h"
#include "LoadOption.h"

namespace Ghurund::Core {
	LoadOption operator |(LoadOption lhs, LoadOption rhs) {
		return (LoadOption)((std::underlying_type<LoadOption>::type)lhs | (std::underlying_type<LoadOption>::type)rhs);
	}

	bool operator &(LoadOption lhs, LoadOption rhs) {
		return (std::underlying_type<LoadOption>::type)lhs & (std::underlying_type<LoadOption>::type)rhs;
	}
}