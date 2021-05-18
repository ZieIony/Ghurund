#pragma once

#include "ResourceFormat.h"
#include "Status.h"
#include "core/allocation/Allocator.h"
#include "core/io/MemoryStream.h"

namespace Ghurund {
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

    class Loader {
    private:
        Allocator* allocator;

    public:
        Loader(Allocator* allocator = nullptr):allocator(allocator) {}

        virtual ~Loader() = 0 {}

        template<class T>
        T* makeResource() {
            if (allocator)
                return (T*)T::TYPE.Constructor->newInstance(*allocator);
            return (T*)T::TYPE.Constructor->newInstance();
        }

        virtual Status load(ResourceManager& manager, MemoryInputStream& stream, Resource& resource, const ResourceFormat* format = nullptr, LoadOption options = LoadOption::DEFAULT) = 0;
        virtual Status save(ResourceManager& manager, MemoryOutputStream& stream, Resource& resource, const ResourceFormat* format = nullptr, SaveOption options = SaveOption::DEFAULT) const = 0;
    };
}