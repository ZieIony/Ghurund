#pragma once

#include "Loader.h"

#include "core/Noncopyable.h"
#include "core/Object.h"
#include "core/collection/PointerMap.h"
#include "core/collection/HashMap.h"
#include "core/logging/Logger.h"
#include "core/io/File.h"
#include "core/io/LibraryList.h"
#include "core/io/MemoryStream.h"
#include "core/io/watcher/FileWatcher.h"
#include "core/resource/ReloadTask.h"
#include "core/resource/Resource.h"
#include "core/threading/WorkerThread.h"

namespace Ghurund {
    class ResourceManager:public Noncopyable, public Object {
    private:
        FileWatcher watcher;
        PointerMap<WString, Resource*> resources;
        LibraryList libraries;
        CriticalSection section;
        Map<const Ghurund::Type*, Loader*> loaders;

        WorkerThread loadingThread;
        List<ReloadTask*> reloadQueue;
        bool hotReloadEnabled
#ifdef _DEBUG
            = true;
#else
            = false;
#endif

        template<class Type> void loadInternal(Type*& resource, const FilePath& path, Status* result, LoadOption options) {
            resource = get<Type>(path);
            Status loadResult;
            if (resource == nullptr) {
                Loader* loader = loaders.get(&Type::TYPE);
                [[likely]]
                if (loader) {
                    resource = loader->makeResource<Type>();
                    loadResult = loadInternal(*loader, *resource, path, options);
                } else {
                    loadResult = Status::LOADER_MISSING;
                }
            } else {
                resource->addReference();
                loadResult = Status::ALREADY_LOADED;
            }
            if (result != nullptr)
                *result = loadResult;
        }

        Status loadInternal(Loader& loader, Resource& resource, const FilePath& path, LoadOption options);

    protected:
        static const Ghurund::Type& GET_TYPE();

    public:
        inline static const wchar_t* const ENGINE_LIB_NAME = L"Ghurund";
        inline static const wchar_t* const LIB_PROTOCOL = L"lib://";

        ResourceManager();

        ~ResourceManager();

        inline void registerLoader(const Ghurund::Type& type, std::unique_ptr<Loader> loader) {
            if (loaders.containsKey(&type)) {
                Loader* loader = loaders.get(&type);
                loaders.remove(&type);
                delete loader;
            }
            loaders.set(&type, loader.release());
        }

        void reload();

        template<class Type> Type* load(const FilePath& path, Status* result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Type* resource;
            loadInternal(resource, path, result, options);
            return resource;
        }

        template<class Type> void loadAsync(const FilePath& path, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Task* task = ghnew Task(path, [this, path, onLoaded, options] {
                Type* resource;
                Status loadResult;
                loadInternal(resource, path, &loadResult, options);
                if (onLoaded != nullptr)
                    onLoaded((Type*)resource, loadResult);
                return loadResult;
            });
            loadingThread.post(task);
            task->release();
        }

        template<class Type> Type* load(const File& file, Status* result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Type* resource;
            loadInternal(resource, file.Path, result, options);
            return resource;
        }

        template<class Type> Type* loadAsync(const File& file, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            FilePath& path = file.Path;
            Task* task = ghnew Task(file.Path, [this, path, onLoaded, options] {
                Type* resource;
                Status loadResult;
                loadInternal(resource, path, &loadResult, options);
                if (onLoaded != nullptr)
                    onLoaded(resource, loadResult);
                return loadResult;
            });
            loadingThread.post(task);
            task->release();
        }

        template<class Type = Resource> Type* load(const DirectoryPath& workingDir, MemoryInputStream& stream, Status* result = nullptr, LoadOption options = LoadOption::DEFAULT) {
            /*size_t index = stream.readUInt();
            const Ghurund::Type& type = Ghurund::Type::TYPES[index];
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

        Status save(Resource& resource, SaveOption options = SaveOption::DEFAULT) const;
        Status save(Resource& resource, const FilePath& path, SaveOption options = SaveOption::DEFAULT) const;
        Status save(Resource& resource, File& file, SaveOption options = SaveOption::DEFAULT) const;
        Status save(Resource& resource, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options = SaveOption::DEFAULT) const;

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

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}
