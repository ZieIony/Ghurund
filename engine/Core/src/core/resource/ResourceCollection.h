#pragma once

#include "Resource.h"
#include "core/object/IntrusivePointer.h"
#include "core/collection/Map.h"

#include <mutex>

namespace Ghurund::Core {
	class ResourceCollection {
	private:
		Map<FilePath, IntrusivePointer<Resource>> resources;
		std::mutex mutex;

	public:
		/**
		* Thread-safe. ResourceManager uses absolute paths if possible.
		**/
		Resource* get(const FilePath& path);

		/**
		* Thread-safe.
		**/
		void put(NotNull<Resource> resource);

		/**
		* Thread-safe.
		**/
		void remove(NotNull<Resource> resource);

		/**
		* Thread-safe. ResourceManager uses absolute paths if possible.
		**/
		void remove(const FilePath& path);

		/**
		* Thread-safe.
		**/
		void clear();

#ifdef _DEBUG
		void validateResources();

		void printResources();
#endif
	};
}
