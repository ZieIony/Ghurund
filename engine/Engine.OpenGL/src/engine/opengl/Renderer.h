#pragma once

#include <Windows.h>
#include <wingdi.h>

#include <core/window/SystemWindow.h>
#include "graphics/RenderingStatistics.h"
#include "core/Object.h"
#include <parameter/ParameterManager.h>
#include <core/Color.h>

namespace Ghurund::Engine::OpenGL {
	using namespace Ghurund::Core;

	class Renderer: public Object {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Renderer::GET_TYPE();
#pragma endregion

	private:
		ParameterManager* parameterManager = nullptr;
		RenderingStatistics stats;

	public:
		void init(ParameterManager& parameterManager);
		void uninit();

		void clear(const Color* color);

		void draw() {
		}

		RenderingStatistics& getStatistics() {
			return stats;
		}

		__declspec(property(get = getStatistics)) RenderingStatistics& Statistics;
	};
}