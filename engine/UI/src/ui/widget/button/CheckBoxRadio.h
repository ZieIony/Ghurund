#pragma once

#include "ui/control/DrawableView.h"
#include "ui/widget/ContentWidget.h"
#include "ui/widget/StateIndicator.h"

#include <tinyxml2.h>

namespace Ghurund::UI {
	template<typename CheckBoxRadioType>
	class CheckBoxRadio:public ContentWidget {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<CheckBoxRadio>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(CheckBoxRadio))
				.withModifiers(TypeModifier::ABSTRACT)
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = CheckBoxRadio::GET_TYPE();
#pragma endregion

	protected:
		bool checked = false;
		InteractionHandler interactionHandler = *this;

		Ghurund::UI::StateIndicator* state = nullptr;
		Ghurund::UI::DrawableView* drawable = nullptr;

		virtual void onLayoutChanged() override {
			if (state) {
				state->InteractionHandler = nullptr;
				state->release();
				state = nullptr;
			}
			safeRelease(drawable);
			__super::onLayoutChanged();
			Control* layoutControl = layout.get();
			if (layoutControl) {
				setPointer(state, (Ghurund::UI::StateIndicator*)layoutControl->find("state"));
				if (state)
					state->InteractionHandler = &interactionHandler;
				setPointer(drawable, (Ghurund::UI::DrawableView*)layoutControl->find("drawable"));
			}
		}

		~CheckBoxRadio() {
			if (state)
				state->release();
			if (drawable)
				drawable->release();
		}

	public:
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