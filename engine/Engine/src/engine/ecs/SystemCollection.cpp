#include "ghepch.h"
#include "SystemCollection.h"

namespace Ghurund::Engine {
	void SystemCollection::add(IntrusivePointer<System> system) {
		system->init();
		auto& dependencies = system->Dependencies;
		uint32_t dependenciesLeft = dependencies.Size;
		for (size_t i = 0; i < systems.Size; i++) {
			if (dependenciesLeft == 0) {
				systems.insert(i, system);
				return;
			}
			for (auto& dependency : dependencies) {
				if (dependency.get() == systems[i]->Type)
					dependenciesLeft--;
			}
		}
		systems.add(system);
	}

#ifdef _DEBUG
	void SystemCollection::printGraph() const {
		Logger::print(LogType::INFO, _T("System graph:\n"));
		for (auto& system : systems) {
			auto message = std::format(_T("{}\n"), system->Type.Name);
			Logger::print(LogType::INFO, message.c_str());
		}
	}
#endif
}
