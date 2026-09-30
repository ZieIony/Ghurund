#pragma once

#include "SampleApplication.h"
#include "engine/application/GameWindow.h"

namespace Sample {
	using namespace Ghurund;
	using namespace Ghurund::Core;

	class SampleWindow:public Ghurund::Engine::GameWindow {
	private:
		SampleApplication& app;
		IntrusivePointer<GameAction<bool>> closeWindow;
		IntrusivePointer<GameAction<XMFLOAT2>> moveWindow;

	public:
		SampleWindow(SampleApplication& app, Ghurund::Engine::OpenGL::OglRenderer& renderer);

		~SampleWindow();

		virtual bool onKeyEvent(const KeyEventArgs& args) override;
	};
}
