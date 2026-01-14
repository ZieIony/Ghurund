#pragma once

#include "MaterialInput.h"

#include "core/collection/Map.h"
#include "core/object/NotNull.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class MaterialInputCollection {
	private:
		// TODO: use HashMap
		Map<AString, MaterialInput*> inputs;

	public:
		~MaterialInputCollection() {
			for (auto& [key, value] : inputs)
				delete value;
		}

		inline void add(NotNull<MaterialInput> input) {
			inputs.put(input->Name, input.get());
		}

		inline MaterialInput* get(const AString& name) const {
			auto it = inputs.find(name);
			if (it == inputs.end())
				return nullptr;
			return it->value;
		}

		inline void clear() {
			for (auto& [key, value] : inputs)
				delete value;
			inputs.clear();
		}
	};
}