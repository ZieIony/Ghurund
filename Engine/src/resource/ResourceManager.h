#pragma once

#include "ResourceContext.h"

#include "audio/Audio.h"
#include "application/log/Logger.h"
#include "core/Noncopyable.h"
#include "core/Object.h"
#include "core/io/File.h"
#include "core/collection/PointerMap.h"
#include "core/collection/HashMap.h"
#include "core/threading/WorkerThread.h"
#include "game/parameter/ParameterManager.h"
#include "graphics/CommandList.h"
#include "resource/LibraryList.h"
#include "resource/ReloadTask.h"
#include "resource/Resource.h"
#include "resource/watcher/FileWatcher.h"

#include <wincodec.h>

namespace Ghurund {
    class ResourceManager:public Noncopyable, public Object {
    private:
		FileWatcher watcher;
        PointerMap<WString, Resource*> resources;
        LibraryList libraries;
        CriticalSection section;

        WorkerThread loadingThread;
        List<ReloadTask*> reloadQueue;
        bool hotReloadEnabled
#ifdef _DEBUG
            = true;
#else
            = false;
#endif

		template<class Type> inline Type* makeResource(ResourceContext& context) {
			const Ghurund::Type& type = Type::TYPE;
			return makeResource<Type>(context, type);
		}

		template<class Type> inline Type* makeResource(ResourceContext& context, const Ghurund::Type& type) {
			Type* resource = nullptr;
			Allocator* allocator = context.Allocators.get(type);
			if (allocator) {
				resource = (Type*)type.Constructor->newInstance(*allocator);
			} else {
				resource = (Type*)type.Constructor->newInstance();
			}
			return resource;
		}

		template<class Type> void loadInternal(Type*& resource, ResourceContext& context, const FilePath& path, Status* result, LoadOption options) {
			FilePath decodedPath = decodePath(path);
			resource = get<Type>(decodedPath);
			Status loadResult = Status::ALREADY_LOADED;
			if (resource == nullptr) {
				resource = makeResource<Type>(context);
				loadResult = loadInternal(*resource, context, decodedPath, options);
				if (filterStatus(loadResult, options) != Status::OK) {
					resource->release();
					resource = nullptr;
				}
			}
			if (result != nullptr)
				*result = loadResult;
		}

		Status loadInternal(Resource& resource, ResourceContext& context, const FilePath& path, LoadOption options);

        FilePath decodePath(const WString& fileName, const DirectoryPath* workingDir = nullptr) const;
        FilePath encodePath(const FilePath& resourcePath, const DirectoryPath& workingDir) const;

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<ResourceManager>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ResourceManager))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    public:
        inline static const wchar_t* const ENGINE_LIB_NAME = L"engine";
        inline static const wchar_t* const LIB_PROTOCOL_PREFIX = L"lib:\\";

        ResourceManager();

        ~ResourceManager();

        void reload();

        template<class Type> Type* load(ResourceContext& context, const FilePath& path, Status* result = nullptr, LoadOption options = LoadOption::DEFAULT) {
			Type* resource;
			loadInternal(resource, context, path, result, options);
            return resource;
        }

        template<class Type> void loadAsync(ResourceContext& context, const FilePath& path, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            Task* task = ghnew Task(String(path), [this, &context, path, onLoaded, options] {
				Type* resource;
				Status loadResult;
				loadInternal(resource, context, path, &loadResult, options);
                if (onLoaded != nullptr)
                    onLoaded((Type*)resource, loadResult);
                return loadResult;
                });
            loadingThread.post(task);
            task->release();
        }

        template<class Type> Type* load(ResourceContext& context, File& file, Status* result = nullptr, LoadOption options = LoadOption::DEFAULT) {
			Type* resource;
			loadInternal(resource, context, file.Path, result, options);
			return resource;
		}

        template<class Type> Type* loadAsync(ResourceContext& context, File& file, std::function<void(Type*, Status)> onLoaded = nullptr, LoadOption options = LoadOption::DEFAULT) {
            FilePath& path = file.Path;
            Task* task = ghnew Task(file.Path, [this, &context, path, onLoaded, options] {
				Type* resource;
				Status loadResult;
				loadInternal(resource, context, path, &loadResult, options);
				if (onLoaded != nullptr)
                    onLoaded(resource, loadResult);
                return loadResult;
            });
            loadingThread.post(task);
            task->release();
        }

        template<class Type = Resource> Type * load(ResourceContext & context, const DirectoryPath & workingDir, MemoryInputStream & stream, Status * result = nullptr, LoadOption options = LoadOption::DEFAULT) {
			size_t index = stream.readUInt();
			const Ghurund::Type& type = Ghurund::Type::TYPES[index];
			Type* resource = makeResource<Type>(context, type);

            Status loadResult;
            if (stream.readBoolean()) {
                loadResult = resource->load(context, workingDir, stream, options);
            } else {
                FilePath decodedPath = decodePath(stream.readUnicode(), &workingDir);
                Type* resource2 = (Type*)get(decodedPath);
                if (resource2) {
                    loadResult = Status::ALREADY_LOADED;
                    resource->release();
                    resource = resource2;
                }else{
                    loadResult = loadInternal(*resource, context, decodedPath, options);
                }
            }
            if (filterStatus(loadResult, options) != Status::OK) {
                resource->release();
                resource = nullptr;
            }
            if (result != nullptr)
                * result = loadResult;
            return resource;
        }

        Status save(Resource& resource, ResourceContext& context, SaveOption options = SaveOption::DEFAULT);
        Status save(Resource& resource, ResourceContext& context, const FilePath& path, SaveOption options = SaveOption::DEFAULT);
        Status save(Resource& resource, ResourceContext& context, File& file, SaveOption options = SaveOption::DEFAULT);
        Status save(Resource& resource, ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options = SaveOption::DEFAULT);

		template<class Type = Resource> Type* get(const WString & fileName) {
			section.enter();
			Resource* resource = nullptr;
			size_t index = resources.findKey(fileName);
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
