#pragma once

#include "DrawPacket.h"
#include "ICamera.h"

#include "core/collection/List.h"

#include <cstdint>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	enum class DrawOrder:int8_t {
		BACK_TO_FRONT = -1, FRONT_TO_BACK = 1
	};

	class RenderGroup {
	private:
		uint32_t order;
		DrawOrder drawOrder;
		ICamera* camera = nullptr;

	public:
		List<DrawPacket> objects;

		// TODO: is this draw order correct?
		RenderGroup(uint32_t order, DrawOrder drawOrder = DrawOrder::FRONT_TO_BACK):order(order), drawOrder(drawOrder) {}

		~RenderGroup() {
			if (camera)
				camera->release();
		}

		// TODO: get sorted objects from here
		inline DrawOrder getDrawOrder() const {
			return drawOrder;
		}

		__declspec(property(get = getDrawOrder)) DrawOrder DrawOrder;

		inline void setCamera(ICamera* camera) {
			setPointer(this->camera, camera);
		}

		inline ICamera* getCamera() const {
			return camera;
		}

		__declspec(property(get = getCamera, put = setCamera)) ICamera* Camera;

		inline auto operator<=>(const RenderGroup& other) const {
			return order <=> other.order;
		}
	};
}