#pragma once

#include "BaseLoader.h"

#include "core/allocation/Allocator.h"
#include "core/concepts/Concepts.h"
#include "core/exception/FormatNotSupportedException.h"
#include "core/io/MemoryInputStream.h"
#include "core/io/MemoryOutputStream.h"
#include "core/reflection/Type.h"
#include "core/resource/LoadOption.h"
#include "core/resource/Resource.h"
#include "core/resource/ResourceFormat.h"
#include "core/resource/SaveOption.h"
#include "core/xml/XMLDocument.h"

#include <cstdint>

namespace Ghurund::Core {
	class ResourceManager;
	class DirectoryPath;

	template<Derived<Resource> T>
	class Loader:public BaseLoader {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<Loader>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = Loader::GET_TYPE();
#pragma endregion

	private:
		Allocator* allocator;

	protected:
		virtual const Ghurund::Core::Type& getResourceType() const override {
			return T::TYPE;
		}

		virtual uint32_t getResourceVersion() const override {
			return T::VERSION;
		}

		inline CoroutineTask<void> loadFromXml(
			T& resource,
			MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOption options
		) {
			auto streamPosition = stream.Position;
			try {
				AString streamContents = stream.readASCII();
				XMLDocument document;
				document.parse(streamContents.Data, (uint32_t)streamContents.Size);
				const XMLElement& root = document.Root;
				co_await loadInternal(resource, root, workingDir, format, options);
			} catch (const std::exception&) {
				stream.Position = streamPosition;
				throw;
			}
		}

		virtual CoroutineTask<void> loadInternal(
			T& resource,
			MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOption options
		) {
			co_await loadFromXml(resource, stream, workingDir, format, options);
		}

		virtual CoroutineTask<void> loadInternal(
			T& resource,
			const XMLElement& xml,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOption options
		) {
			throw NotSupportedException();
		}

		virtual void saveInternal(
			T& resource,
			MemoryOutputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			SaveOption options
		) const {
			throw NotSupportedException();
		}

		virtual void saveInternal(
			T& resource,
			const XMLElement& xml,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			SaveOption options
		) const {
			throw NotSupportedException();
		}

	public:
		Loader(Allocator* allocator = nullptr):allocator(allocator) {}

		virtual ~Loader() = 0 {}

		virtual CoroutineTask<void> load(
			Resource& resource,
			MemoryInputStream& stream,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			LoadOption options = LoadOption::DEFAULT
		) override {
			if (!format.canLoad)
				throw FormatNotSupportedException(format);
			if (resource.IsValid)
				resource.invalidate();
			T& typedResource = castResource<T>(resource);
			co_await loadInternal(typedResource, stream, workingDir, format, options);
		}

		virtual CoroutineTask<void> load(
			Resource& resource,
			const XMLElement& root,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			LoadOption options = LoadOption::DEFAULT
		) override {
			if (!format.canLoad)
				throw FormatNotSupportedException(format);
			if (resource.IsValid)
				resource.invalidate();
			T& typedResource = castResource<T>(resource);
			co_await loadInternal(typedResource, root, workingDir, format, options);
		}

		virtual void save(
			Resource& resource,
			MemoryOutputStream& stream,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			SaveOption options = SaveOption::DEFAULT
		) const override {
			if (!format.canSave)
				throw FormatNotSupportedException(format);
			T& typedResource = castResource<T>(resource);
			saveInternal(typedResource, stream, workingDir, format, options);
		}

		virtual void save(
			Resource& resource,
			const XMLElement& root,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			SaveOption options = SaveOption::DEFAULT
		) const override {
			if (!format.canSave)
				throw FormatNotSupportedException(format);
			T& typedResource = castResource<T>(resource);
			saveInternal(typedResource, root, workingDir, format, options);
		}
	};
}
