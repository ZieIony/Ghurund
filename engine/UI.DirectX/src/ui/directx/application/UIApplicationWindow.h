#pragma once

#include "engine/directx/application/DirectXWindow.h"
#include "ui/RootView.h"
#include "ui/directx/UILayer.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI::DirectX {
	class UIApplicationWindow:public DirectXWindow {
	private:
		DXUILayer* uiLayer = nullptr;
		Ghurund::UI::Theme* theme = nullptr;
		Ghurund::UI::Control* content = nullptr;

	public:
		UIApplicationWindow(Core::Application& app, Renderer& renderer):DirectXWindow(app, renderer) {}

		~UIApplicationWindow() {
			if (uiLayer)
				uiLayer->release();
		}

		virtual void init(WindowManager& windowManager) override {
			__super::init(windowManager);

			uiLayer = ghnew DXUILayer();
			uiLayer->init(*this, SwapChain);
			//Layers.add(uiLayer);

			uiLayer->Root.Theme = theme;
			uiLayer->Root.Child = content;
		}

		inline void setTheme(Ghurund::UI::Theme* theme) {
			this->theme = theme;
			if (uiLayer)
				uiLayer->Root.Theme = theme;
		}

		__declspec(property(put = setTheme)) Ghurund::UI::Theme* Theme;

		inline void setContent(Ghurund::UI::Control* content) {
			this->content = content;
			if (uiLayer)
				uiLayer->Root.Child = content;
		}

		__declspec(property(put = setContent)) Ghurund::UI::Control* Content;

		inline DXUILayer& getUILayer() {
			return *uiLayer;
		}

		__declspec(property(get = getUILayer)) DXUILayer& UILayer;
	};
}