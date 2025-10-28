#pragma once

#include "core/object/NotNull.h"
#include "core/string/String.h"
#include "core/io/File.h"
#include "core/io/LibraryCollection.h"

namespace Ghurund::Core {
	class ResourcePath {
	private:
		enum class Type {
			FILE, LIBRARY
		};

		inline static const WString LIB_PROTOCOL = L"lib://";

		WString libName, path;
		Type type;

	public:
		ResourcePath(const WString& libName, const WString& path):libName(libName), path(path), type(Type::LIBRARY) {}

		ResourcePath(const FilePath& path):path(path), type(Type::FILE) {}

		static ResourcePath parse(const WString& str);

		Library* findLibrary(LibraryCollection& libraries) const {
			if (type == Type::LIBRARY) {
				return libraries.get(libName);
			} else {
				return nullptr;
			}
		}

		ResourcePath getAbsolutePath(const DirectoryPath& workingDir, LibraryCollection& libraries) const {
			if (type == Type::LIBRARY) {
				return libraries.get(libName)->getResourcePath(path);
			} else {
				return FilePath(path).AbsolutePath;
			}
		}

		SharedPointer<Buffer> resolveResource(const DirectoryPath& workingDir, LibraryCollection& libraries) const;

		bool exists(const DirectoryPath& workingDir, const LibraryCollection& libraries) const;

		inline constexpr std::strong_ordering operator<=>(const ResourcePath& other) const noexcept {
			if (type == other.type && path == other.path && libName == other.libName)
				return std::strong_ordering::equal;
			if (libName == other.libName)
				return path <=> other.path;
			return libName <=> other.libName;
		}

		String toString() const;
	};
}