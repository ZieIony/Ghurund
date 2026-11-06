#pragma once

#include "DrawPacket.h"

#include "engine/graphics/Camera.h"
#include "core/collection/List.h"
#include "engine/application/DrawGroup.h"


namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class RenderGroup {
	private:
		DrawGroup group;
		Camera* camera = nullptr;

	public:
		List<DrawPacket> objects;

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
