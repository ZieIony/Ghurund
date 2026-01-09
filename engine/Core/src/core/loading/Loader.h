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

#include <cstdint>

namespace Ghurund::Core {
	class ResourceManager;
	class DirectoryPath;

	class Loader:public RefCountedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Loader::GET_TYPE();
#pragma endregion

	private:
		Allocator* allocator;

	protected:
		template<Derived<Resource> T>
		T* makeResource() {
			Constructor<T>& constructor = (Constructor<T>&)T::GET_TYPE().Constructors.get(0);
			if (allocator)
				return (T*)constructor.invokeWithAllocator(*allocator);
			return (T*)constructor.invoke();
		}

		template<Derived<Resource> T>
		T& castResource(Resource& resource) const {
			if (resource.Type != T::TYPE) {
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

        virtual Resource* loadInternal(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format,
            LoadOption options
        ) {
            throw NotSupportedException();
        }

        virtual void saveInternal(
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat& format,
            SaveOption options
        ) const {
            throw NotSupportedException();
        }

    public:
        Loader(Allocator* allocator = nullptr):allocator(allocator) {}

		virtual ~Loader() = 0 {}

        inline Resource* load(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat& format = ResourceFormat::AUTO,
            LoadOption options = LoadOption::DEFAULT
        ) {
            if (!format.canLoad)
                throw FormatNotSupportedException(format);
            return loadInternal(stream, workingDir, format, options);
        }

        inline void save(
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat& format = ResourceFormat::AUTO,
            SaveOption options = SaveOption::DEFAULT
        ) const {
            if (!format.canSave)
                throw FormatNotSupportedException(format);
            saveInternal(stream, workingDir, resource, format, options);
        }
    };
}