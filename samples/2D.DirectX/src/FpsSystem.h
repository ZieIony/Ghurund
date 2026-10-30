#pragma once

#include "engine/application/GameWindow.h"
#include "engine/ecs/System.h"

namespace Sample {
	using namespace Ghurund::Engine;

	class FpsSystem:public System {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<FpsSystem>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = FpsSystem::GET_TYPE();
#pragma endregion

	private:
		GameWindow& window;

	protected:
		virtual bool getUsesFixedUpdate_internal() const override {
			return false;
		}

	public:
		FpsSystem(GameWindow& window):window(window) {}

		virtual void update(const Timer& timer) override {
			auto text = std::format(_T("fps: {:.2f}"), timer.FramesPerSecond);
			window.Title = String(text.c_str());
		}
	};
}
