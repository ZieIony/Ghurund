#pragma once

#include "engine/application/GameWindow.h"
#include "ui/widget/menu/MenuBarItemAdapter.h"
#include "ui/widget/toolbar/ToolbarItemAdapter.h"
#include <ColorListAdapter.h>
#include <engine/directx/DxRenderer.h>
#include <engine/graphics/texture/ITextureFactory.h>

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
		ITextureFactory& textureFactory;

	public:
		DemoWindow(
			DemoApplication& app,
			Ghurund::Engine::DirectX::DxRenderer& renderer,
			ITextureFactory& textureFactory
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