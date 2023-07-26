#pragma once

#include "ApplicationWindow.h"
#include "ui/RootView.h"
#include "ui/UILayer.h"
#include "ui/theme/Theme.h"

namespace Ghurund {
	class UIApplicationWindow:public ApplicationWindow {
	private:
		Ghurund::UI::UILayer* uiLayer;

	public:
		UIApplicationWindow(Core::Application& app, Renderer& renderer):ApplicationWindow(app, renderer) {}

		~UIApplicationWindow() {
			if (uiLayer)
				uiLayer->release();
		}

		virtual void init(WindowManager& windowManager) override {
			__super::init(windowManager);

			Ghurund::UI::Direct2D::Graphics2D& graphics2d = Application.Features.get<Ghurund::UI::Direct2D::Graphics2D>();
			uiLayer = ghnew Ghurund::UI::UILayer(graphics2d, *this);
			Layers.add(uiLayer);
		}

		inline void setTheme(Ghurund::UI::Theme* theme) {
			uiLayer->Root.Theme = theme;
		}

		__declspec(property(put = setTheme)) Ghurund::UI::Theme* Theme;

		inline void setContent(Ghurund::UI::Control* content) {
			uiLayer->Root.Child = content;
		}

		__declspec(property(put = setContent)) Ghurund::UI::Control* Content;
	};
}