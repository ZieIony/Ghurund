#pragma once

#include "ui/control/InteractionHandler.h"
#include "ui/widget/ContentWidget.h"
#include "ui/widget/StateIndicator.h"

namespace Ghurund::UI {
	class Button:public ContentWidget {
	private:
		InteractionHandler interactionHandler = *this;
		Ghurund::UI::StateIndicator* state = nullptr;

	protected:
		virtual void onLayoutChanged() override;

		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		__declspec(property(get = getType)) const Ghurund::Core::Type& Type;

		Event<Button, MouseClickedEventArgs> clicked = *this;

		Button() {
			Focusable = true;
		}

		Button(const Button& button):ContentWidget(button) {}

		~Button() {
			if (state)
				state->release();
		}

		virtual Button* clone() const override {
			return ghnew Button(*this);
		}
	};
}