#pragma once

#include "core/allocation/Allocator.h"
#include "core/concepts/Concepts.h"
#include "core/exception/FormatNotSupportedException.h"
#include "core/io/MemoryInputStream.h"
#include "core/io/MemoryOutputStream.h"
#include "core/logging/Logger.h"
#include "core/object/RefCountedObject.h"
#include "core/reflection/Type.h"
#include "core/resource/LoadOption.h"
#include "core/resource/Resource.h"
#include "core/resource/ResourceFormat.h"
#include "core/resource/SaveOption.h"
#include "core/xml/XMLElement.h"
#include "core/coroutine/CoroutineTask.h"
#include "core/object/IntrusivePointer.h"

#include <cstdint>

namespace Ghurund::Core {
	class ResourceManager;
	class DirectoryPath;

	class BaseLoader:public RefCountedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = BaseLoader::GET_TYPE();
#pragma endregion

	private:
		Allocator* allocator;

	protected:
		virtual const Ghurund::Core::Type& getResourceType() const = 0;

		virtual uint32_t getResourceVersion() const = 0;

		inline Resource* makeResource() {
			auto& constructor = getResourceType().Constructors.get(0).get();
			if (allocator)
				return (Resource*)constructor.invokeRawWithAllocator(*allocator);
			return (Resource*)constructor.invokeRaw();
		}

		template<Derived<Resource> T>
		T& castResource(Resource& resource) const {
			if (!resource.Type.isOrExtends(T::TYPE)) {
				Logger::log(LogType::ERR0R, std::format(_T("resource needs to be of type {}\n"), T::TYPE.Name).c_str());
				throw std::invalid_argument(std::format("resource needs to be of type {}", T::TYPE.Name).c_str());
			}
			return (T&)resource;
		}

		template<Derived<Resource> T>
		void writeHeader(MemoryOutputStream& stream) const {
			unsigned int hash = hashCode(T::TYPE.Name.Data);
			stream.writeUInt32(hash);
			stream.writeUInt32(T::VERSION);
		}

		template<Derived<Resource> T>
		void readHeader(MemoryInputStream& stream) {
			readHeader(stream, T::TYPE, T::VERSION);
		}

		void readHeader(MemoryInputStream& stream, const Ghurund::Core::Type& type, uint32_t version);

		void checkXmlRoot(const XMLElement& xml, const WString& name);

	public:
		BaseLoader(Allocator* allocator = nullptr):allocator(allocator) {}

		virtual ~BaseLoader() = 0 {}

		virtual CoroutineTask<void> load(
			Resource& resource,
			MemoryInputStream& stream,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			LoadOption options = LoadOption::DEFAULT
		) = 0;

		virtual CoroutineTask<IntrusivePointer<Resource>> load(
			MemoryInputStream& stream,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			LoadOption options = LoadOption::DEFAULT
		) {
			auto resource = IntrusivePointer(makeResource());
			co_await load(resource.ref(), stream, workingDir, format, options);
			co_return resource;
		}

		virtual CoroutineTask<void> load(
			Resource& resource,
			const XMLElement& xml,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			LoadOption options = LoadOption::DEFAULT
		) = 0;

		virtual CoroutineTask<IntrusivePointer<Resource>> load(
			const XMLElement& xml,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			LoadOption options = LoadOption::DEFAULT
		) {
			auto resource = IntrusivePointer(makeResource());
			co_await load(resource.ref(), xml, workingDir, format, options);
			co_return resource;
		}

		virtual void save(
			Resource& resource,
			MemoryOutputStream& stream,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			SaveOption options = SaveOption::DEFAULT
		) const = 0;

		virtual void save(
			Resource& resource,
			const XMLElement& xml,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			SaveOption options = SaveOption::DEFAULT
		) const = 0;
	};
}
