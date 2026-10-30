#pragma once

#include "System.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class SystemCollection {
	private:
		struct SystemGroup {
			List<IntrusivePointer<System>> systems;
		};

		List<IntrusivePointer<System>> systems;

	public:
		SystemCollection() {}

		~SystemCollection() {
			clear();
		}

		void add(IntrusivePointer<System> system);

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

#ifdef _DEBUG
		void printGraph() const;
#endif
	};
}
