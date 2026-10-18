#pragma once

#include "ResourceFormat.h"

#include "core/io/FilePath.h"
#include "core/object/NamedObject.h"
#include "core/object/RefCountedObject.h"
#include "core/Event.h"

namespace Ghurund::Core {
	struct DataSize {
		// TODO: consider 32b sizes
		uint64_t graphical, system;
	};

	class ResourceManager;
	class MemoryInputStream;
	class MemoryOutputStream;
	class File;

	enum class ResourceState {
		// a path may be set, but the rest is missing
		EMPTY,
		// the resource was loaded, but can't be used yet, for example because it still needs to be uploaded to VRAM
		LOADED,
		// the resource is ready to use
		INITIALIZED
	};

	class Resource: public RefCountedObject, public WStringNamedObject {
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
		ResourceState state = ResourceState::EMPTY;
		FilePath* path = nullptr;

	protected:
		DataSize dataSize = {};

		Resource() {}

		Resource(const Resource& other):
			state(other.state),
			path(other.path ? ghnew FilePath(*other.path) : nullptr),
			dataSize(other.dataSize) {}

		~Resource();

		inline void setState(ResourceState newState) {
			auto prevState = state;
			state = newState;
			stateChanged(prevState);
		}

	public:
		// needed for TileMapComponent, but maybe it could be done in a different way?
		Event<Resource, void, ResourceState> stateChanged = *this;

		inline ResourceState getState() const {
			return state;
		}

		__declspec(property(get = getState, put = setState)) ResourceState State;

		const FilePath* getPath() const {
			return path;
		}

		/**
		* Also sets resource name to path/nullptr if name == path.
		**/
		void setPath(const FilePath* path);

		__declspec(property(get = getPath, put = setPath)) FilePath* Path;
		
		const DataSize& getDataSize() const {
			return dataSize;
		}

		__declspec(property(get = getDataSize)) const DataSize& DataSize;

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
