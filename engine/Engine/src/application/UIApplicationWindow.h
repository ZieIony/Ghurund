#pragma once

#include "ApplicationWindow.h"
#include "ui/RootView.h"
#include "ui/UILayer.h"
#include "ui/theme/Theme.h"

namespace Ghurund {
	class UIApplicationWindow:public ApplicationWindow {
	private:
		Ghurund::UI::UILayer* uiLayer = nullptr;
		Ghurund::UI::Theme* theme = nullptr;
		Ghurund::UI::Control* content = nullptr;

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
	};
}