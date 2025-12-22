#include "ghcpch.h"
#include "Resource.h"

#include "core/logging/Formatter.h"
#include "core/reflection/TypeBuilder.h"

#include <format>

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

	String Resource::toString() const {
		if (path) {
			return String(std::format(_T("{}, path: {}"), __super::toString(), path->toString()).c_str());
		} else {
			return __super::toString();
		}
	}
}