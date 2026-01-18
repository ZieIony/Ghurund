#pragma once

#include "ui/control/ImageView.h"
#include "ui/control/InteractionHandler.h"
#include "ui/widget/ContentWidget.h"

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class CheckBoxRadio:public ContentWidget {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = CheckBoxRadio::GET_TYPE();
#pragma endregion

	protected:
		bool checked = false;
		InteractionHandler interactionHandler = *this;
		IntrusivePointer<ImageView> iconView;
		FloatInput* checkedParameter = nullptr;
		FloatInput* checkedParameter2 = nullptr;

		virtual void onLayoutChanged() override;

		virtual void onMaterialChanged() override;

	public:
		CheckBoxRadio() {
			Focusable = true;
		}
	};
}