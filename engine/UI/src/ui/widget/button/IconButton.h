#pragma once

#include "ui/control/InteractionHandler.h"
#include "ui/theme/ThemedValueProperty.h"
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
		//PointerAttrProperty<DrawableAttr, Drawable> drawable;
		ThemedValueProperty<ColorKey, Color*> tint;

		inline void setThemedTint(std::unique_ptr<ThemedColor> tint) {
			if (!tint) {
				setTint(nullptr);
			} else if (tint->Key) {
				setTint(*tint->Key);
			} else {
				setTint(tint->Value);
			}
		}

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

		inline void setTint(nullptr_t) {
			this->tint.set(nullptr);
			updateProperties();
		}

		inline void setTint(const ColorKey& tint) {
			this->tint.set(tint);
			updateProperties();
		}

		inline void setTint(const Color& tint) {
			this->tint.set(tint);
			updateProperties();
		}

		__declspec(property(put = setTint)) const Color& Tint;

		virtual IconButton* clone() const override {
			return ghnew IconButton(*this);
		}
	};
}