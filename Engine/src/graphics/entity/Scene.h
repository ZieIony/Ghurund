#pragma once

#include "ecs/Entity.h"
#include "resource/Resource.h"
#include "physics/Physics.h"
#include "physics/PhysicsSystem.h"
#include "graphics/GraphicsSystem.h"

namespace Ghurund {
	class Scene :public Resource {
	private:
		inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Scene>();
	
		PointerList<Entity*> entities;
		TransformSystem transformSystem;
		PhysicsSystem physicsSystem;
		GraphicsSystem graphicsSystem;

	protected:
		virtual Status loadInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryInputStream& stream, LoadOption options) override;
		virtual Status saveInternal(ResourceContext& context, const DirectoryPath& workingDir, MemoryOutputStream& stream, SaveOption options) const override;

	public:

		Scene() {}

		void init(Camera* camera, ResourceContext& context) {
			graphicsSystem.Camera = camera;
			graphicsSystem.init(context.Graphics);
			graphicsSystem.initParameters(context.ParameterManager);
		}

		PointerList<Entity*>& getEntities() {
			return entities;
		}

		__declspec(property(get = getEntities)) PointerList<Entity*>& Entities;

		TransformSystem& getTransformSystem() {
			return transformSystem;
		}

		__declspec(property(get = getTransformSystem)) TransformSystem& TransformSystem;

		GraphicsSystem& getGraphicsSystem() {
			return graphicsSystem;
		}

		__declspec(property(get = getGraphicsSystem)) GraphicsSystem& GraphicsSystem;

		void transform() {
			transformSystem.update(0);
		}

		void render(CommandList& commandList) {
			graphicsSystem.draw(commandList, transformSystem);
		}

		inline static const Ghurund::Type& TYPE = Ghurund::Type(CONSTRUCTOR, "Ghurund", "Scene");

		virtual const Ghurund::Type& getType() const override {
			return TYPE;
		}

		static const Array<ResourceFormat*>& getFormats() {
			static const Array<ResourceFormat*> formats = { (ResourceFormat*)& ResourceFormat::SCENE };
			return formats;
		}

		__declspec(property(get = getFormats)) Array<ResourceFormat*>& Formats;
	};
}