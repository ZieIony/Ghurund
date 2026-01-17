#pragma once

#include "core/reflection/Property.h"
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
		static const Ghurund::Core::Type& GET_TYPE() {
			static const Ghurund::Core::Type TYPE = TypeBuilder<CheckBoxRadio>()
				.withSupertype(__super::GET_TYPE());

			return TYPE;
		}

		inline static const Ghurund::Core::Type& TYPE = CheckBoxRadio::GET_TYPE();
#pragma endregion

	protected:
		bool checked = false;
		InteractionHandler interactionHandler = *this;
		IntrusivePointer<ImageView> iconView;
		FloatInput* checkedParameter = nullptr;
		FloatInput* checkedParameter2 = nullptr;

		virtual void onLayoutChanged() override {
			iconView.set(nullptr);
			__super::onLayoutChanged();
			Control* layoutControl = layout.get();
			if (layoutControl) {
				iconView.set((Ghurund::UI::ImageView*)layoutControl->find("icon"));
				iconView->addReference();
					checkedParameter2 = (FloatInput*)iconView->Material->Inputs.get("checked");
			}
		}

		virtual void onMaterialChanged() override {
			if (material != nullptr) {
				checkedParameter = (FloatInput*)material->Inputs.get("checked");
			} else {
				checkedParameter = nullptr;
			}
		}

	public:
		CheckBoxRadio() {
			Focusable = true;
		}
	};
}