#pragma once

#include "ui/control/InteractionHandler.h"
#include "ui/style/AttrProperty.h"
#include "ui/style/ColorAttr.h"
#include "ui/widget/StateIndicator.h"
#include "ui/widget/Widget.h"

namespace Ghurund::UI {
	class IconButton:public Widget {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = IconButton::GET_TYPE();
#pragma endregion

	private:
		InteractionHandler interactionHandler = *this;
		Ghurund::UI::StateIndicator* state = nullptr;
		//PointerAttrProperty<DrawableAttr, Drawable> drawable;
		NullableAttrProperty<ColorAttr, Color> tint;

		inline void updateProperties() {
			/*if (drawableView) {
				drawableView->Drawable = drawable;
				drawableView->Tint = tint;
			}*/
		}

	protected:
		IconButton(const IconButton& button):Widget(button) {}

		virtual void onLayoutChanged() override;

	public:
		Event<IconButton, MouseClickedEventArgs> clicked = *this;

		IconButton() {
			Focusable = true;
			interactionHandler.clicked += [this](InteractionHandler&, const MouseClickedEventArgs& args) {
				return clicked(args);
			};
		}

		~IconButton() {
			if (state)
				state->release();
		}

		/*inline void setDrawable(std::unique_ptr<DrawableAttr> drawable) {
			this->drawable.set(std::move(drawable));
			updateProperties();
		}

		inline void setDrawable(const TextureKey& key) {
			this->drawable.set(std::make_unique<DrawableRef>(key));
			updateProperties();
		}

		inline void setDrawable(Drawable* drawable) {
			this->drawable.set(std::make_unique<DrawableValue>(drawable));
			updateProperties();
		}

		inline void setDrawable(const PointerAttrProperty<DrawableAttr, Drawable>& drawable) {
			this->drawable = drawable;
			updateProperties();
		}

		__declspec(property(put = setDrawable)) std::unique_ptr<DrawableAttr>& Drawable;*/

		inline void setTint(std::unique_ptr<ColorAttr> tint) {
			this->tint.set(std::move(tint));
			updateProperties();
		}

		inline void setTint(const ColorKey& tint) {
			this->tint.set(std::make_unique<ColorRef>(tint));
			updateProperties();
		}

		inline void setTint(Color tint) {
			this->tint.set(std::make_unique<ColorValue>(tint));
			updateProperties();
		}

		inline void setTint(const NullableAttrProperty<ColorAttr, Color>& tint) {
			this->tint = tint;
			updateProperties();
		}

		__declspec(property(put = setTint)) std::unique_ptr<ColorAttr> Tint;

		virtual IconButton* clone() const override {
			return ghnew IconButton(*this);
		}
	};
}