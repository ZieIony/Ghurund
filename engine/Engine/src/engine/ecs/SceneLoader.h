#pragma once

#include "Scene.h"

#include "core/loading/Loader.h"
#include "core/object/NotNull.h"
#include "engine/ecs/ComponentLoader.h"

namespace Ghurund::Engine {

	class SceneLoader:public Ghurund::Core::Loader<Scene> {
	private:
		Map<WString, IntrusivePointer<ComponentLoader>> componentLoaders;

		void loadEntity(Scene& resource, const XMLElement& entityElement, const DirectoryPath& workingDir);

	protected:
		virtual CoroutineTask<void> load_internal(
			Scene& resource,
			const XMLElement& xml,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			LoadOptions options
		) override;

		virtual void save_internal(
			Scene& resource,
			MemoryOutputStream& stream,
			const DirectoryPath& workingDir,
			const ResourceFormat& format,
			SaveOptions options
		) const override;

	public:
		inline void addComponentLoader(NotNull<ComponentLoader> loader) {
			auto intrusivePointer = IntrusivePointer<ComponentLoader>(loader.get());
			intrusivePointer->addReference();
			componentLoaders.put(loader->getComponentName(), intrusivePointer);
		}
	};
}
