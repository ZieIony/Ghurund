#pragma once

#include <Windows.h>
#include <wingdi.h>

#include "core/Color.h"
#include "core/window/SystemWindow.h"
#include "engine/graphics/Renderer.h"
#include "engine/graphics/RenderingStatistics.h"
#include "engine/parameter/ParameterManager.h"
#include "OglRenderingContext.h"

namespace Ghurund::Engine::OpenGL {
	using namespace Ghurund::Core;

	class OglRenderer: public Renderer {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = OglRenderer::GET_TYPE();
#pragma endregion

	private:
		ParameterManager* parameterManager = nullptr;

	protected:
		virtual void onInit() override;

	public:
		OglRenderer(NotNull<ParameterManager> parameterManager):parameterManager(&parameterManager) {}

		virtual OglRenderingContext* makeRenderingContext(NotNull<SystemWindow> window) override {
			return ghnew OglRenderingContext(window);
		}
	};
}