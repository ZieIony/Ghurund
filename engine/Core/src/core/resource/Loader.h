#pragma once

#include "LoadOption.h"
#include "SaveOption.h"
#include "ResourceFormat.h"
#include "core/RefCountedObject.h"
#include "core/allocation/Allocator.h"
#include "core/exception/FormatNotSupportedException.h"
#include "core/io/MemoryInputStream.h"
#include "core/io/MemoryOutputStream.h"
#include "core/reflection/Type.h"

namespace Ghurund::Core {
    class Resource;
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
        template<class T>
        T* makeResource() {
            Constructor<T>& constructor = (Constructor<T>&)T::GET_TYPE().Constructors.get(0);
            if (allocator)
                return (T*)constructor.invokeWithAllocator(*allocator);
            return (T*)constructor.invoke();
        }

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