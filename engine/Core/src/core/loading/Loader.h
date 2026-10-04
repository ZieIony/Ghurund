#pragma once

#include "BaseLoader.h"

#include "core/allocation/Allocator.h"
#include "core/concepts/Derived.h"
#include "core/exception/FormatNotSupportedException.h"
#include "core/io/MemoryInputStream.h"
#include "core/io/MemoryOutputStream.h"
#include "core/reflection/Type.h"
#include "core/resource/LoadOptions.h"
#include "core/resource/Resource.h"
#include "core/resource/ResourceFormat.h"
#include "core/resource/SaveOptions.h"
#include "core/xml/XMLDocument.h"

#include <cstdint>

namespace Ghurund::Core {
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

		virtual const ResourceFormat& getPreferredSaveFormat() const {
			return ResourceFormat::AUTO;
		}

		[[nodiscard]]
		inline CoroutineTask<void> loadFromXml(
			T& resource,
			MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOptions options
		) {
			auto streamPosition = stream.Position;
			try {
				AString streamContents = stream.readAString();
				XMLDocument document;
				document.parse(streamContents.Data, (uint32_t)streamContents.Size);
				const XMLElement& root = document.Root;
				co_await loadInternal(resource, root, workingDir, format, options);
			} catch (...) {
				stream.Position = streamPosition;
				std::exception_ptr exception = std::current_exception();
				std::rethrow_exception(exception);
			}
		}

		[[nodiscard]]
		virtual CoroutineTask<void> loadInternal(
			T& resource,
			MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOptions options
		) {
			co_await loadFromXml(resource, stream, workingDir, format, options);
		}

		[[nodiscard]]
		virtual CoroutineTask<void> loadInternal(
			T& resource,
			const XMLElement& xml,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOptions options
		) {
			throw NotSupportedException();
		}

		virtual void saveInternal(
			T& resource,
			MemoryOutputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			SaveOptions options
		) const {
			throw NotSupportedException();
		}

		virtual void saveInternal(
			T& resource,
			const XMLElement& xml,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			SaveOptions options
		) const {
			throw NotSupportedException();
		}

	public:
		Loader(Allocator* allocator = nullptr):allocator(allocator) {}

		virtual ~Loader() = 0 {}

		[[nodiscard]]
		virtual CoroutineTask<void> load(
			Resource& resource,
			MemoryInputStream& stream,
			const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			LoadOptions options = {}
		) override {
			if (!format.CanLoad)
				throw FormatNotSupportedException(format);
			if (resource.IsValid)
				resource.invalidate();
			T& typedResource = castResource<T>(resource);
			co_await loadInternal(typedResource, stream, workingDir, format, options);
		}

		[[nodiscard]]
		virtual CoroutineTask<void> load(
			Resource& resource,
			const XMLElement& root,
			const DirectoryPath& workingDir = DirectoryPath(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			LoadOptions options = {}
		) override {
			if (!format.CanLoad)
				throw FormatNotSupportedException(format);
			if (resource.IsValid)
				resource.invalidate();
			T& typedResource = castResource<T>(resource);
			co_await loadInternal(typedResource, root, workingDir, format, options);
		}

		virtual void save(
			Resource& resource,
			MemoryOutputStream& stream,
			const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			SaveOptions options = {}
		) const override {
			auto resolvedFormat = format;
			if (format == ResourceFormat::AUTO)
				resolvedFormat = getPreferredSaveFormat();
			if (!resolvedFormat.CanSave)
				throw FormatNotSupportedException(resolvedFormat);
			T& typedResource = castResource<T>(resource);
			saveInternal(typedResource, stream, workingDir, resolvedFormat, options);
		}

		virtual void save(
			Resource& resource,
			const XMLElement& root,
			const DirectoryPath& workingDir = DirectoryPath::getCurrentDirectory(),
			const ResourceFormat& format = ResourceFormat::AUTO,
			SaveOptions options = {}
		) const override {
			auto resolvedFormat = format;
			if (format == ResourceFormat::AUTO)
				resolvedFormat = getPreferredSaveFormat();
			if (!resolvedFormat.CanSave)
				throw FormatNotSupportedException(resolvedFormat);
			T& typedResource = castResource<T>(resource);
			saveInternal(typedResource, root, workingDir, resolvedFormat, options);
		}
	};
}
