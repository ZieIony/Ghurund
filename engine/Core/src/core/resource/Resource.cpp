#include "ghcpch.h"
#include "Resource.h"

#include "core/io/MemoryInputStream.h"
#include "core/io/MemoryOutputStream.h"
#include "core/logging/Formatter.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::Core {
	const Ghurund::Core::Type& Resource::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Resource>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	Resource::~Resource() {
		delete path;
	}

    void Resource::setPath(const ResourcePath* path) {
        delete this->path;
        if (path) {
            this->path = ghnew ResourcePath(*path);
        } else {
            this->path = nullptr;
        }
	}
}