#pragma once

#include <exception>

namespace Ghurund::Core {
	class InvalidVersionException:public std::exception {
	public:
		const uint32_t fileVersion, supportedVersion;

		InvalidVersionException(
			uint32_t fileVersion,
			uint32_t supportedVersion
		):fileVersion(fileVersion), supportedVersion(supportedVersion) {}
	};
}
