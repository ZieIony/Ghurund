#pragma once

#include "ui/control/ClickableControl.h"
#include "ui/widget/ContentWidget.h"
#include "ui/widget/StateIndicator.h"

namespace Ghurund::UI {
	class Button:public ContentWidget {
	private:
		Ghurund::UI::ClickableControl* clickable = nullptr;
		Ghurund::UI::StateIndicator* state = nullptr;

		EventHandler<Control> stateHandler = [this](Control& control) {
			if (clickable && state) {
				if (clickable->Pressed) {
					state->State = IndicatorState::PRESSED;
				} else if (clickable->Focused || clickable->Hovered) {
					state->State = IndicatorState::FOCUSED;
				} else {
					state->State = IndicatorState::NONE;
				}
				return true;
			}
			return false;
		};

		EventHandler<Control, MouseClickedEventArgs> clickHandler = [this](Control&, const MouseClickedEventArgs& args) {
			return clicked(args);
		};

	protected:
		virtual void onLayoutChanged() override;

		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		__declspec(property(get = getType)) const Ghurund::Core::Type& Type;

		Event<Button, MouseClickedEventArgs> clicked = *this;

		~Button() {
			if (clickable)
				clickable->release();
			if (state)
				state->release();
		}
	};
}