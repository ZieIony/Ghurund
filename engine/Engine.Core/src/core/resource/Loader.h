#pragma once

#include "ResourceFormat.h"
#include "Status.h"
#include "core/Pointer.h"
#include "core/allocation/Allocator.h"
#include "core/io/MemoryStream.h"
#include "core/reflection/Constructor.h"

namespace Ghurund::Core {
    enum class LoadOption {
        DEFAULT = 0, DONT_WATCH = 1, DONT_CACHE = 2
    };

    LoadOption operator |(LoadOption lhs, LoadOption rhs);

    bool operator &(LoadOption lhs, LoadOption rhs);

    enum class SaveOption {
        DEFAULT = 0, OVERWRITE = 1, SKIP_IF_EXISTS = 2
    };

    SaveOption operator |(SaveOption lhs, SaveOption rhs);

    bool operator &(SaveOption lhs, SaveOption rhs);

    class Resource;
    class ResourceManager;

    class Loader:public Pointer {
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

    public:
        Loader(Allocator* allocator = nullptr):allocator(allocator) {}

        virtual ~Loader() = 0 {}

        virtual Resource* load(
            MemoryInputStream& stream,
            const DirectoryPath& workingDir,
            const ResourceFormat* format = nullptr,
            LoadOption options = LoadOption::DEFAULT
        ) = 0;

        virtual void save(
            MemoryOutputStream& stream,
            const DirectoryPath& workingDir,
            Resource& resource,
            const ResourceFormat* format = nullptr,
            SaveOption options = SaveOption::DEFAULT
        ) const = 0;
    };
}