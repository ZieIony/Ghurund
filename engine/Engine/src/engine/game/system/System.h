#pragma once

#include "core/object/Initializable.h"
#include "engine/game/GameObject.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class System:public GameObject, public Initializable {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = System::GET_TYPE();
#pragma endregion

	protected:
		virtual bool getUsesDrawInternal() const override {
			return false;
		}
	};
}
