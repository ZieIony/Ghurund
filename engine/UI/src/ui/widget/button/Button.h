#pragma once

#include "ui/control/InteractionHandler.h"
#include "ui/widget/ContentWidget.h"

namespace Ghurund::UI {
	class Button:public ContentWidget {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Button::GET_TYPE();
#pragma endregion

	private:
		InteractionHandler interactionHandler = *this;

	protected:
		Button(const Button& button):ContentWidget(button) {}

	public:
		Event<Button, MouseClickedEventArgs> clicked = *this;

		Button() {
			Focusable = true;
			interactionHandler.clicked += [this](InteractionHandler&, const MouseClickedEventArgs& args) {
				return clicked(args);
			};
		}

		virtual Button* clone() const override {
			return ghnew Button(*this);
		}
	};
}