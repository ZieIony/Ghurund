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
				co_await load_internal(resource, root, workingDir, format, options);
			} catch (...) {
				stream.Position = streamPosition;
				std::exception_ptr exception = std::current_exception();
				std::rethrow_exception(exception);
			}
		}

		[[nodiscard]]
		virtual CoroutineTask<void> load_internal(
			T& resource,
			MemoryInputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOptions options
		) {
			co_await loadFromXml(resource, stream, workingDir, format, options);
		}

		[[nodiscard]]
		virtual CoroutineTask<void> load_internal(
			T& resource,
			const XMLElement& xml,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOptions options
		) {
			throw NotSupportedException();
		}

		[[nodiscard]]
		virtual CoroutineTask<void> init_internal(T& resource) {
			co_return;
		}

		[[nodiscard]]
		virtual CoroutineTask<void> deinit_internal(T& resource) {
			co_return;
		}

		[[nodiscard]]
		virtual CoroutineTask<void> unload_internal(T& resource) {
			co_return;
		}

		virtual void save_internal(
			T& resource,
			MemoryOutputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			SaveOptions options
		) const {
			throw NotSupportedException();
		}

		virtual void save_internal(
			T& resource,
			const XMLElement& xml,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			SaveOptions options
		) const {
			throw NotSupportedException();
		}

	public:
		virtual ~Loader() = 0 {}

		[[nodiscard]]
		virtual IntrusivePointer<Resource> makeResource() const override {
			return makeIntrusive<T>();
		}

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
#ifdef _DEBUG
			_ASSERTE(resource.State == ResourceState::EMPTY);
#endif
			T& typedResource = castResource<T>(resource);
			co_await load_internal(typedResource, stream, workingDir, format, options);
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
#ifdef _DEBUG
			_ASSERTE(resource.State == ResourceState::EMPTY);
#endif
			T& typedResource = castResource<T>(resource);
			co_await load_internal(typedResource, root, workingDir, format, options);
		}

		[[nodiscard]]
		virtual CoroutineTask<void> init(Resource& resource) override {
			T& typedResource = castResource<T>(resource);
			co_await init_internal(typedResource);
		}

		[[nodiscard]]
		virtual CoroutineTask<void> deinit(Resource& resource) override {
			T& typedResource = castResource<T>(resource);
			co_await deinit_internal(typedResource);
		}

		[[nodiscard]]
		virtual CoroutineTask<void> unload(Resource& resource) override {
			T& typedResource = castResource<T>(resource);
			co_await unload_internal(typedResource);
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
#ifdef _DEBUG
			_ASSERTE(resource.State != ResourceState::EMPTY);
#endif
			T& typedResource = castResource<T>(resource);
			save_internal(typedResource, stream, workingDir, resolvedFormat, options);
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
#ifdef _DEBUG
			_ASSERTE(resource.State != ResourceState::EMPTY);
#endif
			T& typedResource = castResource<T>(resource);
			save_internal(typedResource, root, workingDir, resolvedFormat, options);
		}
	};
}
