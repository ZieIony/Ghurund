#pragma once

#include "core/string/String.h"

namespace Ghurund::Core {

	class Path {
	protected:
		WString path;

	public:
		static const inline WString SEPARATOR = L"/";

		Path(const WString& path):path(path) {
			this->path.replaceAll(L'\\', L'/');
		}

		Path(Path&& path) noexcept {
			this->path = std::move(path.path);
		}

		virtual ~Path() = 0 {}

		Path& operator=(const Path& other) {
			if (this == &other)
				return *this;
			path = other.path;
			return *this;
		}

		Path& operator=(Path&& other) noexcept {
			if (this == &other)
				return *this;
			path = std::move(other.path);
			return *this;
		}

		// TODO: this method name looks like it's costly to call - maybe it should be a getter instead?
		const WString& toString() const {
			return path;
		}

		size_t getLength() const {
			return path.Length;
		}

		__declspec(property(get = getLength)) size_t Length;

		bool getIsAbsolute() const;

		__declspec(property(get = getIsAbsolute)) bool IsAbsolute;

		bool getIsLibrary() const;

		__declspec(property(get = getIsLibrary)) bool IsLibrary;

		bool operator==(const Path& otherPath) const {
			return path == otherPath.path;
		}

		bool operator==(const Path& otherPath) {
			return path == otherPath.path;
		}

		constexpr std::strong_ordering operator<=>(const Path& other) const noexcept {
			return path <=> other.path;
		}
	};
}
