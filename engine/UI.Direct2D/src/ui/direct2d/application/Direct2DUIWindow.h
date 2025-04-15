#pragma once

#include "engine/directx/application/DirectXWindow.h"
#include "ui/RootView.h"
#include "ui/direct2d/UILayer.h"
#include "ui/theme/Theme.h"

namespace Ghurund::UI::Direct2D {
	class Direct2DUIWindow:public DirectXWindow {
	private:
		Ghurund::UI::Direct2D::D2DUILayer* uiLayer = nullptr;

	public:
		Direct2DUIWindow(Core::Application& app, Renderer& renderer):DirectXWindow(app, renderer) {}

		virtual void init() override {
			__super::init();

			Ghurund::UI::Direct2D::Graphics2D& graphics2d = Application.Features.get<Ghurund::UI::Direct2D::Graphics2D>();
			uiLayer = ghnew Ghurund::UI::Direct2D::D2DUILayer();
			uiLayer->init(graphics2d, *this, SwapChain);
			Layers.add(uiLayer);
		}

		virtual void uninit() override {
			if (uiLayer)
				uiLayer->release();
			__super::uninit();
		}

		inline void setTheme(Ghurund::UI::Theme* theme) {
			uiLayer->Root.Theme = theme;
		}

		__declspec(property(put = setTheme)) Ghurund::UI::Theme* Theme;

		inline Control* getContent() {
			return uiLayer->Content;
		}

		inline void setContent(Ghurund::UI::Control* content) {
			uiLayer->Content = content;
		}

		__declspec(property(put = setContent)) Ghurund::UI::Control* Content;

		inline Ghurund::UI::Direct2D::D2DUILayer& getUILayer() {
			return *uiLayer;
		}

		__declspec(property(get = getUILayer)) Ghurund::UI::Direct2D::D2DUILayer& UILayer;
	};
}