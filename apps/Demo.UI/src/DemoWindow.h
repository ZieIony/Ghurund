#pragma once

#include "ui/widget/menu/MenuBarItemAdapter.h"
#include "ui/widget/toolbar/ToolbarItemAdapter.h"
#include <ColorListAdapter.h>
#include <ui/UIDebugTools.h>
#include "engine/directx/application/DirectXWindow.h"

namespace Demo {
	using namespace Ghurund;
	using namespace Ghurund::Core;

	class DemoApplication;

	class DemoWindow:public Ghurund::Engine::DirectX::DirectXWindow {
	private:
		IntrusivePointer<Control> demoLayout;
		ColorListAdapter* adapter1 = nullptr, * adapter2 = nullptr;
		ToolbarItemAdapter* toolbarItemAdapter = nullptr;
		MenuBarItemAdapter* menuBarItemAdapter = nullptr;
		DemoApplication& app;

	public:
		DemoWindow(DemoApplication& app, Ghurund::Engine::DirectX::Renderer& renderer);

		~DemoWindow() {
			delete adapter1;
			delete adapter2;
			delete toolbarItemAdapter;
			delete menuBarItemAdapter;
			UIDebugTools::uninit();
		}

		virtual void init() override;
	};
}