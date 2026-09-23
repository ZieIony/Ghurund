#pragma once

#include "FilePath.h"
#include "core/collection/List.h"

namespace Ghurund::Core {

	class DirectoryPath:public Path {
	private:
		WString combineStr(const WString& str) const;

	public:
		DirectoryPath(const WString& path):Path(path) {
			if (!this->path.endsWith(L"/"))
				this->path.add(L'/');
		}

		DirectoryPath(const DirectoryPath& path):DirectoryPath(path.path) {}

		DirectoryPath(DirectoryPath&& path) noexcept:Path(std::move(path)) {}

		inline DirectoryPath& operator=(const DirectoryPath& other) {
			if (this == &other)
				return *this;
			__super::operator=(other);
			return *this;
		}

		inline DirectoryPath& operator=(DirectoryPath&& other) noexcept {
			if (this == &other)
				return *this;
			__super::operator=(std::move(other));
			return *this;
		}

		static DirectoryPath getCurrentDirectory();

		inline DirectoryPath getRelativePath(const DirectoryPath& dir) const {
			if (path.startsWith(dir.toString().Data))
				return path.substring(dir.Length);
			return path;
		}

		//__declspec(property(get = getRelativePath)) DirectoryPath RelativePath;

		DirectoryPath getAbsolutePath() const;

		__declspec(property(get = getAbsolutePath)) DirectoryPath AbsolutePath;

		DirectoryPath combine(const DirectoryPath& dir) const;

		inline DirectoryPath operator/(const DirectoryPath& dir) const {
			return combine(dir);
		}

		FilePath combine(const FilePath& file) const;

		inline FilePath operator/(const FilePath& file) const {
			return combine(file);
		}

		List<DirectoryPath> getDirectories() const;

		__declspec(property(get = getDirectories)) List<DirectoryPath> Directories;

		List<FilePath> getFiles() const;

		__declspec(property(get = getFiles)) List<FilePath> Files;
	};
}