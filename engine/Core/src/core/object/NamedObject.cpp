#include "ghcpch.h"
#include "NamedObject.h"

namespace Ghurund::Core {
	template<>
	const Type& getType<WStringNamedObject>() {
		static Type TYPE = TypeBuilder<WStringNamedObject>();
		return TYPE;
	}

	template<>
	const Type& getType<AStringNamedObject>() {
		static Type TYPE = TypeBuilder<AStringNamedObject>();
		return TYPE;
	}
}
