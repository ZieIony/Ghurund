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

    void Resource::setPath(const FilePath* path) {
		if (this->path == path)
			return;
        delete this->path;
        if (path) {
            this->path = ghnew FilePath(*path);
			if (!Name)
				Name = path->toString();
        } else {
			if (*Name == this->path->toString())
				Name = nullptr;
            this->path = nullptr;
        }
	}

	String Resource::toString() const {
		if (Name) {
			String nameStr = convertText<wchar_t, tchar>(*Name);
			return nameStr;
		} else if (path) {
			String pathStr = convertText<wchar_t, tchar>(path->toString());
			return pathStr;
		} else {
			return __super::toString();
		}
	}
}
