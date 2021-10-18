#pragma once

#include "Loader.h"
#include "LoaderCollection.h"
#include "ReloadTask.h"
#include "Resource.h"
#include "ResourceFormat.h"

#include "core/Noncopyable.h"
#include "core/Object.h"
#include "core/collection/PointerMap.h"
#include "core/collection/HashMap.h"
#include "core/logging/Logger.h"
#include "core/io/File.h"
#include "core/io/LibraryList.h"
#include "core/io/MemoryStream.h"
#include "core/io/watcher/FileWatcher.h"
#include "core/threading/WorkerThread.h"

namespace Ghurund::Core {
    class ResourceManager:public Noncopyable, public Object {
    private:
        FileWatcher watcher;
        Map<WString, SharedPointer<Resource>> resources;
        LibraryList libraries;
        CriticalSection section;
        LoaderCollection loaders;

        WorkerThread loadingThread;
        List<ReloadTask*> reloadQueue;
        bool hotReloadEnabled
#ifdef _DEBUG
            = true;
#else
            = false;
#endif

        Status loadInternal(Loader& loader, Resource& resource, const FilePath& path, const ResourceFormat* format, LoadOption options);
        Status loadInternal(Loader& loader, Resource& resource, const File& file, const ResourceFormat* format, LoadOption options);
        Status loadInternal(Loader& loader, Resource& resource, MemoryInputStream& stream, const ResourceFormat* format, LoadOption options);

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const wchar_t* const ENGINE_LIB_NAME = L"Ghurund";
        inline static const wchar_t* const LIB_PROTOCOL = L"lib://";
        inline static const wchar_t* const FILE_PROTOCOL = L"file://";

        ResourceManager();

        ~ResourceManager();

        inline LoaderCollection& getLoaders() {
            return loaders;
        }

        __declspec(property(get = getLoaders)) LoaderCollection& Loaders;

        void reload();

        template<class Type> Type* load(const FilePath& path, const ResourceFormat* format = nullptr, Status* result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            // TODO: resolve path earlier to detect duplicates with differently written paths
            Type* resource = get<Type>(path);
            Status loadResult;
            if (resource == nullptr) {
                Loader* loader = loaders.get<Type>();
                [[likely]]
                if (loader) {
                    resource = loader->makeResource<Type>();
                    loadResult = loadInternal(*loader, *resource, path, format, options);
                    if (loadResult != Status::OK) {
                        resource->release();
                        resource = nullptr;
                    }
                } else {
                    loadResult = Status::LOADER_MISSING;
                    resource->release();
                    resource = nullptr;
                }
            } else {
                resource->addReference();
                loadResult = Status::ALREADY_LOADED;
            }
            if (result != nullptr)
                *result = loadResult;
            return resource;
        }

        template<class Type> void loadAsync(const FilePath& path, const ResourceFormat* format = nullptr, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Task* task = ghnew Task(path, [this, path, format, onLoaded, options] {
                Status loadResult;
                Type* resource = load(path, format, &loadResult, options);
                if (onLoaded != nullptr)
                    onLoaded((Type*)resource, loadResult);
                return loadResult;
            });
            loadingThread.post(task);
            task->release();
        }

        template<class Type> Type* load(const File& file, const ResourceFormat* format = nullptr, Status* result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Type* resource = get<Type>(file.Path);
            Status loadResult;
            if (resource == nullptr) {
                Loader* loader = loaders.get<Type>();
                [[likely]]
                if (loader) {
                    resource = loader->makeResource<Type>();
                    loadResult = loadInternal(*loader, *resource, file, format, options);
                } else {
                    loadResult = Status::LOADER_MISSING;
                }
            } else {
                resource->addReference();
                loadResult = Status::ALREADY_LOADED;
            }
            if (result != nullptr)
                *result = loadResult;
            return resource;
        }

        template<class Type> Type* loadAsync(const File& file, const ResourceFormat* format = nullptr, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Task* task = ghnew Task(file.Path, [this, file, format, onLoaded, options] {
                Status loadResult;
                Type* resource = load(resource, file, format, &loadResult, options);
                if (onLoaded != nullptr)
                    onLoaded(resource, loadResult);
                return loadResult;
            });
            loadingThread.post(task);
            task->release();
        }

        template<class Type = Resource> Type* load(const DirectoryPath& workingDir, MemoryInputStream& stream, Status* result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            /*size_t index = stream.readUInt();
            const Ghurund::Core::Type& type = Ghurund::Core::Type::TYPES[index];
            Type* resource = makeResource<Type>(context, type);

            Status loadResult;
            if (stream.readBoolean()) {
                loadResult = resource->load(context, workingDir, stream, options);
            } else {
                FilePath path = WString(stream.readUnicode());
                Type* resource2 = (Type*)get(path);
                if (resource2) {
                    loadResult = Status::ALREADY_LOADED;
                    resource->release();
                    resource = resource2;
                } else {
                    loadResult = loadInternal(*resource, context, path, options);
                }
            }
            if (filterStatus(loadResult, options) != Status::OK) {
                resource->release();
                resource = nullptr;
            }
            if (result != nullptr)
                *result = loadResult;
            return resource;*/
            return nullptr;
        }

        Status save(Resource& resource, const ResourceFormat* format = nullptr, SaveOption options = SaveOption::DEFAULT) const;
        Status save(Resource& resource, const FilePath& path, const ResourceFormat* format = nullptr, SaveOption options = SaveOption::DEFAULT) const;
        Status save(Resource& resource, File& file, const ResourceFormat* format = nullptr, SaveOption options = SaveOption::DEFAULT) const;
        Status save(Resource& resource, const DirectoryPath& workingDir, MemoryOutputStream& stream, const ResourceFormat* format = nullptr, SaveOption options = SaveOption::DEFAULT) const;

        template<class Type = Resource> Type* get(const WString& fileName) {
            section.enter();
            Resource* resource = nullptr;
            size_t index = resources.indexOfKey(fileName);
            if (index != resources.Size)
                resource = resources.getValue(index);
            section.leave();
            return (Type*)resource;
        }

        void add(Resource& resource);

        void remove(const WString& fileName);

        void clear();

        void setHotReloadEnabled(bool enabled) {
            this->hotReloadEnabled = enabled;
        }

        bool isHotReloadEnabled() {
            return hotReloadEnabled;
        }

        __declspec(property(get = isHotReloadEnabled, put = setHotReloadEnabled)) bool HotReloadEnabled;

        LibraryList& getLibraries() {
            return libraries;
        }

        __declspec(property(get = getLibraries)) LibraryList& Libraries;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };
}
