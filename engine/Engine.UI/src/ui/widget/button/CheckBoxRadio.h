#pragma once

#include "ui/control/SelectableView.h"
#include "ui/control/DrawableView.h"
#include "ui/widget/ContentWidget.h"
#include "ui/widget/StateIndicator.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
	template<typename CheckBoxRadioType>
	class CheckBoxRadio:public ContentWidget {
	protected:
		bool checked = false;

		Ghurund::UI::SelectableView* clickable = nullptr;
		Ghurund::UI::StateIndicator* state = nullptr;
		Ghurund::UI::DrawableView* drawable = nullptr;

		EventHandler<Control> stateHandler = [this](Control& control) {
			/*if (clickable->Pressed) {
				state->State = IndicatorState::PRESSED;
			} else if (clickable->Focused || clickable->Hovered) {
				state->State = IndicatorState::FOCUSED;
			} else {
				state->State = IndicatorState::NONE;
			}*/
			return true;
			};

		virtual void onLayoutChanged() override {
			safeRelease(clickable);
			safeRelease(state);
			safeRelease(drawable);
			__super::onLayoutChanged();
			Control* layoutControl = layout.get();
			if (layoutControl) {
				setPointer(clickable, (Ghurund::UI::SelectableView*)layoutControl->find("clickable"));
				if (!clickable)
					throw InvalidDataException("layout is missing 'clickable' SelectableView");
				setPointer(state, (Ghurund::UI::StateIndicator*)layoutControl->find("state"));
				if (!state)
					throw InvalidDataException("layout is missing 'state' StateIndicator");
				setPointer(drawable, (Ghurund::UI::DrawableView*)layoutControl->find("drawable"));
			} else {
				clickable = nullptr;
				state = nullptr;
				drawable = nullptr;
			}
		}

		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

		~CheckBoxRadio() {
			if (clickable)
				clickable->release();
			if (state)
				state->release();
			if (drawable)
				drawable->release();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<CheckBoxRadio>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(CheckBoxRadio))
				.withModifiers(TypeModifier::ABSTRACT)
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		__declspec(property(get = getType)) const Ghurund::Core::Type& Type;

		Event<CheckBoxRadioType, bool> checkedChanged = Event<CheckBoxRadioType, bool>((CheckBoxRadioType&)*this);

		inline void setChecked(bool checked) {
			if (this->checked != checked) {
				this->checked = checked;
				dispatchStateChanged();
				checkedChanged(checked);
			}
		}

		__declspec(property(put = setChecked)) bool Checked;
	};
}