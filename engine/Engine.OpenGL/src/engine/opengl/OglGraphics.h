#pragma once

#include "engine/opengl/OglRenderer.h"
#include "core/feature/Feature.h"

namespace Ghurund::Engine::OpenGL {
	class OglGraphics: public Ghurund::Core::Feature {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = OglGraphics::GET_TYPE();
#pragma endregion

	private:
		OglRenderer* renderer = nullptr;
		OglRenderingContext* context = nullptr;
		SystemWindow* window = nullptr;

		void uninitGraphics();

	protected:
		virtual void onInit() override;

		virtual void onUninit() override {
			uninitGraphics();
		};

	public:
		~OglGraphics() {
			if (IsInitialized)
				uninitGraphics();
		}
	};
}