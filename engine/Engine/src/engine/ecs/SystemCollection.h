#pragma once

#include "System.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class SystemCollection {
	private:
		List<IntrusivePointer<System>> systems;

	public:
		SystemCollection() {}

		~SystemCollection() {
			clear();
		}

		inline void add(IntrusivePointer<System> system) {
			system->init();
			systems.add(system);
		}

		template<Derived<System> T>
		inline T* get() {
			for (auto& system : systems) {
				if (system->Type == getType<T>())
					return (T*)system.get();
			}
			return nullptr;
		}

		inline void remove(IntrusivePointer<System> system) {
			systems.remove(system);
			system->deinit();
		}

		inline void clear() {
			while (!systems.IsEmpty) {
				auto system = systems.get(systems.Size - 1);
				systems.removeAt(systems.Size - 1);
				system->deinit();
			}
		}

		virtual void fixedUpdate(const Timer& timer) {
			for (auto& system : systems) {
				if (system->isEnabled && system->UsesFixedUpdate)
					system->fixedUpdate(timer);
			}
		}

		virtual void update(const Timer& timer) {
			for (auto& system : systems) {
				if (system->isEnabled && system->UsesUpdate)
					system->update(timer);
			}
		}

		inline void queueDraw(RenderingContext& renderingContext) {
			for (auto& system : systems) {
				if (system->isEnabled && system->UsesDraw)
					system->queueDraw(renderingContext);
			}
		}
	};
}
