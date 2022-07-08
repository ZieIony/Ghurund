#pragma once

#include "Loader.h"
#include "LoaderCollection.h"
#include "ReloadTask.h"
#include "Resource.h"
#include "ResourceFormat.h"

#include "core/Exceptions.h"
#include "core/Noncopyable.h"
#include "core/Object.h"
#include "core/collection/HashMap.h"
#include "core/logging/Logger.h"
#include "core/logging/Formatter.h"
#include "core/io/File.h"
#include "core/io/LibraryList.h"
#include "core/io/MemoryStream.h"
#include "core/io/watcher/FileWatcher.h"
#include "core/threading/WorkerThread.h"

#include <format>

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

        Resource* loadInternal(Loader& loader, const FilePath& path, const ResourceFormat* format, LoadOption options);
        Resource* loadInternal(Loader& loader, const File& file, const ResourceFormat* format, LoadOption options);

        void saveInternal(Resource& resource, Loader& loader, File& file, const ResourceFormat* format, SaveOption options) const;

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

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

        template<class Type> Type* load(const FilePath& path, const ResourceFormat* format = nullptr, LoadOption options = LoadOption::DEFAULT) {
            // TODO: resolve path earlier to detect duplicates with differently written paths
            Type* resource = get<Type>(path); // TODO: why it doesn't find fonts?
            if (resource == nullptr) {
                Loader* loader = loaders.get<Type>();
                [[likely]]
                if (loader) {
                    resource = (Type*)loadInternal(*loader, path, format, options);
                } else {
                    auto message = std::format(_T("loader for type {} is missing\n"), ((const Ghurund::Core::Type&)Type::GET_TYPE()).Name);
                    Logger::log(LogType::ERR0R, message.c_str());
                    auto exMessage = convertText<tchar, char>(String(message.c_str()));
                    throw InvalidStateException(exMessage.Data);
                }
            } else {
                resource->addReference();
            }
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

        template<class Type> Type* load(const File& file, const ResourceFormat* format = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Type* resource = get<Type>(file.Path);
            if (resource == nullptr) {
                Loader* loader = loaders.get<Type>();
                [[likely]]
                if (loader) {
                    resource = (Type*)loadInternal(*loader, file, format, options);
                } else {
                    auto message = std::format(_T("loader for type {} is missing\n"), Type::GET_TYPE().Name);
                    Logger::log(LogType::ERR0R, message.c_str());
                    AString exMessage = convertText<tchar, char>(String(message.c_str()));
                    throw InvalidStateException(exMessage.Data);
                }
            } else {
                resource->addReference();
            }
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

        template<class Type> void save(Type& resource, const ResourceFormat* format = nullptr, SaveOption options = SaveOption::DEFAULT) const {
            Loader* loader = loaders.get<Type>();
            [[likely]]
            if (loader) {
                File file(resource.Path);
                resource = (Type*)saveInternal(resource, *loader, file, format, options);
            } else {
                auto message = std::format(_T("loader for type {} is missing\n"), ((const Ghurund::Core::Type&)Type::GET_TYPE()).Name);
                Logger::log(LogType::ERR0R, message.c_str());
                auto exMessage = convertText<tchar, char>(String(message.c_str()));
                throw InvalidStateException(exMessage.Data);
            }
        }

        template<class Type> void save(Type& resource, const FilePath& path, const ResourceFormat* format = nullptr, SaveOption options = SaveOption::DEFAULT) const {
            Loader* loader = loaders.get<Type>();
            [[likely]]
            if (loader) {
                File file(path);
                saveInternal(resource, *loader, file, format, options);
                file.write();
            } else {
                auto message = std::format(_T("loader for type {} is missing\n"), ((const Ghurund::Core::Type&)Type::GET_TYPE()).Name);
                Logger::log(LogType::ERR0R, message.c_str());
                auto exMessage = convertText<tchar, char>(String(message.c_str()));
                throw InvalidStateException(exMessage.Data);
            }
        }

        template<class Type> void save(Type& resource, File& file, const ResourceFormat* format = nullptr, SaveOption options = SaveOption::DEFAULT) const {
            Loader* loader = loaders.get<Type>();
            [[likely]]
            if (loader) {
                resource = (Type*)saveInternal(resource, *loader, file, format, options);
            } else {
                auto message = std::format(_T("loader for type {} is missing\n"), ((const Ghurund::Core::Type&)Type::GET_TYPE()).Name);
                Logger::log(LogType::ERR0R, message.c_str());
                auto exMessage = convertText<tchar, char>(String(message.c_str()));
                throw InvalidStateException(exMessage.Data);
            }
        }

        template<class Type> void save(Type& resource, const DirectoryPath& workingDir, MemoryOutputStream& stream, const ResourceFormat* format = nullptr, SaveOption options = SaveOption::DEFAULT) const {
            /*Loader* loader = loaders.get<Type>();
            [[likely]]
            if (loader) {
                resource = (Type*)saveInternal(resource, *loader, format, options);
            } else {
                auto message = std::format(_T("loader for type {} is missing\n"), ((const Ghurund::Core::Type&)Type::GET_TYPE()).Name);
                Logger::log(LogType::ERR0R, message.c_str());
                auto exMessage = convertText<tchar, char>(String(message.c_str()));
                throw InvalidStateException(exMessage.Data);
            }*/
        }

        template<class Type = Resource> Type* get(const WString& fileName) {
            section.enter();
            Resource* resource = nullptr;
            size_t index = resources.indexOfKey(fileName);
            if (index != resources.Size)
                resource = resources.getValue(index).get();
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

        static const Ghurund::Core::Type& GET_TYPE();
   };
}
