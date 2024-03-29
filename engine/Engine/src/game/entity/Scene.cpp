#include "ghpch.h"
#include "Scene.h"

namespace Ghurund {
	Status Scene::loadInternal(const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) {
        /*context.Allocators.set(DrawableComponent::TYPE, DrawingSystem.Allocator);
		size_t size = stream.readUInt();
		for (size_t i = 0; i < size; i++) {
			Status result;
			Resource* resource = context.ResourceManager.load(context, workingDir, stream, &result, options);
			if (resource == nullptr)
				return result;
			entities.add((Entity*)resource);
			resource->release();
		}*/
		return Status::OK;
	}

	Status Scene::saveInternal(const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const {
		/*stream.writeUInt((uint32_t)entities.Size);
		for (size_t i = 0; i < entities.Size; i++) {
			Status result = context.ResourceManager.save(*entities[i], context, workingDir, stream, options);
			if (filterStatus(result, options) != Status::OK)
				return result;
		}*/
		return Status::OK;
	}
	
	const Ghurund::Core::Type& Scene::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<Scene>();
		static const Ghurund::Core::Type TYPE = TypeBuilder<Scene>(Ghurund::NAMESPACE_NAME, GH_STRINGIFY(Scene))
			.withConstructor(CONSTRUCTOR)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}
}
