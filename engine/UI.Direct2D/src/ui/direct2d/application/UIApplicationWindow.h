#pragma once

#include "engine/directx/application/DirectXWindow.h"
#include "ui/RootView.h"
#include "ui/direct2d/UILayer.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI::Direct2D {
	class UIApplicationWindow:public DirectXWindow {
	private:
		Ghurund::UI::Direct2D::D2DUILayer* uiLayer = nullptr;
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

			Ghurund::UI::Direct2D::Graphics2D& graphics2d = Application.Features.get<Ghurund::UI::Direct2D::Graphics2D>();
			uiLayer = ghnew Ghurund::UI::Direct2D::D2DUILayer();
			uiLayer->init(graphics2d, *this, SwapChain);
			Layers.add(uiLayer);

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

		inline Ghurund::UI::UILayer & getUILayer() {
			return *uiLayer;
		}

		__declspec(property(get = getUILayer)) Ghurund::UI::UILayer& UILayer;
	};
}