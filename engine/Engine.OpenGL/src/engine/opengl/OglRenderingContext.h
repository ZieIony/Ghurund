#pragma once

#include "engine/graphics/RenderingContext.h"

#include <Windows.h>

namespace Ghurund::Engine::OpenGL {
    using namespace Ghurund::Core;

	class OglRenderingContext: public Ghurund::Engine::RenderingContext {
    private:
        HDC dc = {};
        HGLRC renderContext = {};

	protected:
		virtual void onInit() override;

		virtual void onUninit() override;
		void uninitRenderingContext();

	public:
        OglRenderingContext(SystemWindow& window):Ghurund::Engine::RenderingContext(window) {}

		~OglRenderingContext() {
			if (IsInitialized)
				uninitRenderingContext();
		}

        virtual void startFrame() override;

        virtual void finishFrame() override;
		
		virtual void clear(const Color* color) override;

		virtual void draw(Set<RenderGroup>& renderGroups, ParameterManager& parameterManager) override;

        virtual void setSize(Ghurund::Core::IntSize size) override;
	};
}