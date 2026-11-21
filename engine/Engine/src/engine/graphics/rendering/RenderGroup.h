#pragma once

#include "DrawPacket.h"

#include "engine/graphics/Camera.h"
#include "core/collection/List.h"
#include "engine/application/DrawGroup.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	struct BatchId {
		uint32_t meshId, materialId;

		constexpr std::strong_ordering operator<=>(const BatchId& other) const noexcept {
			auto result = meshId <=> other.meshId;
			if (result != 0)
				return result;
			return materialId <=> other.materialId;
		}
	};

	struct DrawBatch {
		Mesh* mesh;
		Material* material;
		List<uint32_t> instances;
	};

	class RenderGroup {
	private:
		DrawGroup group;
		Camera* camera = nullptr;

	public:
		Map<BatchId, DrawBatch> objects;

		RenderGroup(DrawGroup group):group(group) {}

		~RenderGroup() {
			if (camera)
				camera->release();
		}

		// TODO: get sorted objects from here
		inline DrawGroup getDrawGroup() const {
			return group;
		}

		__declspec(property(get = getDrawGroup)) DrawGroup DrawGroup;

		inline void setCamera(Camera* camera) {
			setPointer(this->camera, camera);
		}

		inline Camera* getCamera() const {
			return camera;
		}

		__declspec(property(get = getCamera, put = setCamera)) Camera* Camera;

		inline auto operator<=>(const RenderGroup& other) const {
			return group.DrawOrder <=> other.group.DrawOrder;
		}
	};
}
