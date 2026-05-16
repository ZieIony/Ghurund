#pragma once

#include "GameObject.h"

#include "core/object/IntrusivePointer.h"
#include "engine/application/DrawGroup.h"

#include <map>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class GameObjectDrawCollection {
	private:
		std::map<DrawGroup, std::vector<IntrusivePointer<GameObject>>> drawObjects;

	public:
		inline void add(IntrusivePointer<GameObject> object) {
			if (object->UsesDraw) {
				auto it = drawObjects.find(object->drawGroup);
				if (it == drawObjects.end()) {
					drawObjects.emplace(object->drawGroup, std::vector({ object }));
				} else {
					drawObjects[object->drawGroup].push_back(object);
				}
			}
		}

		inline void remove(IntrusivePointer<GameObject> object) {
			if (object->UsesDraw) {
				auto& v = drawObjects[object->drawGroup];
				v.erase(std::find(v.begin(), v.end(), object));
			}
		}

		inline void draw(RenderGroup& rg) {
			for (auto& group : drawObjects) {
				for (auto& object : group.second) {
					if (object->isEnabled)
						object->draw(rg);
				}
			}
		}
	};
}
