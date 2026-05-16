#pragma once

#include "GameObject.h"

#include "core/object/IntrusivePointer.h"
#include "engine/application/UpdateGroup.h"

#include <map>

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class GameObjectUpdateCollection {
	private:
		std::map<UpdateGroup, std::vector<IntrusivePointer<GameObject>>> preFixedUpdateObjects, postFixedUpdateObjects;
		std::map<UpdateGroup, std::vector<IntrusivePointer<GameObject>>> preUpdateObjects, postUpdateObjects;

	public:
		inline void add(IntrusivePointer<GameObject> object) {
			if (object->UsesFixedUpdate) {
				if (object->updateGroup.GroupOrder < 0) {
					auto it = preFixedUpdateObjects.find(object->updateGroup);
					if (it == preFixedUpdateObjects.end()) {
						preFixedUpdateObjects.emplace(object->updateGroup, std::vector({ object }));
					} else {
						preFixedUpdateObjects[object->updateGroup].push_back(object);
					}
				} else {
					auto it = postFixedUpdateObjects.find(object->updateGroup);
					if (it == postFixedUpdateObjects.end()) {
						postFixedUpdateObjects.emplace(object->updateGroup, std::vector({ object }));
					} else {
						postFixedUpdateObjects[object->updateGroup].push_back(object);
					}
				}
			}
			if (object->UsesUpdate) {
				if (object->updateGroup.GroupOrder < 0) {
					auto it = preUpdateObjects.find(object->updateGroup);
					if (it == preUpdateObjects.end()) {
						preUpdateObjects.emplace(object->updateGroup, std::vector({ object }));
					} else {
						preUpdateObjects[object->updateGroup].push_back(object);
					}
				} else {
					auto it = postUpdateObjects.find(object->updateGroup);
					if (it == postUpdateObjects.end()) {
						postUpdateObjects.emplace(object->updateGroup, std::vector({ object }));
					} else {
						postUpdateObjects[object->updateGroup].push_back(object);
					}
				}
			}
		}

		inline void remove(IntrusivePointer<GameObject> object) {
			if (object->UsesFixedUpdate) {
				if (object->updateGroup.GroupOrder < 0) {
					auto& v = preFixedUpdateObjects[object->updateGroup];
					v.erase(std::find(v.begin(), v.end(), object));
				} else {
					auto& v = postFixedUpdateObjects[object->updateGroup];
					v.erase(std::find(v.begin(), v.end(), object));
				}
			}
			if (object->UsesUpdate) {
				if (object->updateGroup.GroupOrder < 0) {
					auto& v = preUpdateObjects[object->updateGroup];
					v.erase(std::find(v.begin(), v.end(), object));
				} else {
					auto& v = postUpdateObjects[object->updateGroup];
					v.erase(std::find(v.begin(), v.end(), object));
				}
			}
		}

		inline void preFixedUpdate(const Timer& timer) {
			for (auto& group : preFixedUpdateObjects) {
				for (auto& object : group.second) {
					if (object->isEnabled)
						object->fixedUpdate(timer);
				}
			}
		}

		inline void postFixedUpdate(const Timer& timer) {
			for (auto& group : postFixedUpdateObjects) {
				for (auto& object : group.second) {
					if (object->isEnabled)
						object->fixedUpdate(timer);
				}
			}
		}

		inline void preUpdate(const Timer& timer) {
			for (auto& group : preUpdateObjects) {
				for (auto& object : group.second) {
					if (object->isEnabled)
						object->update(timer);
				}
			}
		}

		inline void postUpdate(const Timer& timer) {
			for (auto& group : postUpdateObjects) {
				for (auto& object : group.second) {
					if (object->isEnabled)
						object->update(timer);
				}
			}
		}
	};
}
