#pragma once

#include "Common.h"
#include "FilePath.h"
#include "core/string/String.h"
#include "core/Buffer.h"

namespace Ghurund::Core {
	class File {
	private:
		FilePath path;

	public:
		File(const FilePath& path):path(path.AbsolutePath) {}

		File(const File& other):path(path) {}

		File(File&& other) noexcept:path(std::move(other.path)) {}

		inline File& operator=(const File& other) {
			if (this == &other)
				return *this;
			path = other.path;
			return *this;
		}

		inline File& operator=(File&& other) noexcept {
			if (this == &other)
				return *this;
			path = std::move(other.path);
			return *this;
		}

		const size_t getSize() const;

		__declspec(property(get = getSize)) size_t Size;

		const FilePath& getPath() const { return path; }

		void setPath(const FilePath& val) {
			this->path = val.AbsolutePath;
		}

		__declspec(property(get = getPath, put = setPath)) FilePath& Path;

		void read(Buffer& buffer) const;

		void read(void*& data, size_t& size) const;

		void write(const void* data, size_t size) const;

		void write(const Buffer& buffer) const;

		bool exists() const;

		__declspec(property(get = exists)) bool Exists;
	};
}