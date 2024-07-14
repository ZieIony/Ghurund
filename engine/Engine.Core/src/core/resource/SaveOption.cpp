#include "ghcpch.h"
#include "SaveOption.h"

namespace Ghurund::Core {
	SaveOption operator |(SaveOption lhs, SaveOption rhs) {
		return (SaveOption)((std::underlying_type<SaveOption>::type)lhs | (std::underlying_type<SaveOption>::type)rhs);
	}

	bool operator &(SaveOption lhs, SaveOption rhs) {
		return (std::underlying_type<SaveOption>::type)lhs & (std::underlying_type<SaveOption>::type)rhs;
	}
}