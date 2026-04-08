#pragma once

#include "ResourceFormat.h"

#include "core/io/FilePath.h"
#include "core/object/RefCountedObject.h"
#include <core/Event.h>

namespace Ghurund::Core {
	struct DataSize {
		uint64_t graphical, system;
	};

	class ResourceManager;
	class MemoryInputStream;
	class MemoryOutputStream;
	class File;

	class Resource: public RefCountedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Resource::GET_TYPE();
#pragma endregion

	private:
		bool valid = false;
		FilePath* path = nullptr;

	protected:
		DataSize dataSize = {};

		Resource() {}

		Resource(const Resource& other):
			path(other.path ? ghnew FilePath(*other.path) : nullptr),
			dataSize(other.dataSize) {}

		~Resource();

	public:
		Event<Resource> validChanged = *this;

		virtual void invalidate() {
			valid = false;
			validChanged();
		}

		inline void validate() {
			valid = true;
			validChanged();
		}

		virtual bool getIsValid() const {
			return valid;
		}

		__declspec(property(get = getIsValid)) bool IsValid;

		const FilePath* getPath() const {
			return path;
		}

		void setPath(const FilePath* path);

		__declspec(property(get = getPath, put = setPath)) FilePath* Path;
		/*
		const DataSize& getSize() const {
			return dataSize;
		}

		__declspec(property(get = getSize)) const DataSize& Size;*/

		virtual String toString() const override;

	protected:
		virtual const Array<ResourceFormat>& getFormatsImpl() const {
			return FORMATS;
		}

	public:
		inline static const Array<ResourceFormat>& FORMATS = {};

		inline const Array<ResourceFormat>& getFormats() const {
			return getFormatsImpl();
		}

		__declspec(property(get = getFormats)) Array<ResourceFormat>& Formats;
	};
}