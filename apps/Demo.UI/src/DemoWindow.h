#pragma once

#include "engine/application/GameWindow.h"
#include "ui/loading/DrawableFactory.h"
#include "ui/widget/menu/MenuBarItemAdapter.h"
#include "ui/widget/toolbar/ToolbarItemAdapter.h"
#include <ColorListAdapter.h>
#include <engine/directx/DxRenderer.h>

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;

	class DemoApplication;

	class DemoWindow:public Ghurund::Engine::GameWindow {
	private:
		IntrusivePointer<Control> demoLayout;
		ColorListAdapter* adapter1 = nullptr, * adapter2 = nullptr;
		ToolbarItemAdapter* toolbarItemAdapter = nullptr;
		MenuBarItemAdapter* menuBarItemAdapter = nullptr;
		// borrowed
		Ghurund::UI::DrawableFactory* drawableFactory;

	public:
		DemoWindow(
			DemoApplication& app,
			Ghurund::Engine::DirectX::DxRenderer& renderer,
			Ghurund::UI::DrawableFactory& drawableFactory
		);

		~DemoWindow() {
			delete adapter1;
			delete adapter2;
			delete toolbarItemAdapter;
			delete menuBarItemAdapter;
		}

		void init();
	};
}