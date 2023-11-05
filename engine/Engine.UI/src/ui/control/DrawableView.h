#pragma once

#include "Control.h"
#include "ui/Alignment.h"
#include "ui/drawable/Drawable.h"
#include "ui/style/PointerAttrProperty.h"
#include "ui/style/AttrProperty.h"
#include "ui/style/ColorAttr.h"
#include "ui/style/DrawableAttr.h"
#include "ImageScaleMode.h"

namespace Ghurund::UI {
	class DrawableView: public Control {
	private:
		PointerAttrProperty<DrawableAttr, Drawable> drawable;
		NullableAttrProperty<ColorAttr, Color> tint;
		ImageScaleMode scaleMode = ImageScaleMode::CROP;
		Alignment gravity;

		inline void updateProperties() {
			const UI::Theme* theme = Theme;
			if (theme) {
				tint.resolve(*theme);
				drawable.resolve(*theme);
			}
		}

	protected:
		virtual void onThemeChanged() override;

		virtual void onStateChanged() override {
			/*if (Enabled) {
				drawable->Alpha = 1.0f;
			} else {
				Alpha = 0.38f;
			}*/
		}

		virtual void onMeasure() override;

		virtual void onDraw(Ghurund::UI::ICanvas& canvas) override;

		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = DrawableView::GET_TYPE();

		DrawableView() {
			gravity.horizontal = Alignment::Horizontal::CENTER;
			gravity.vertical = Alignment::Vertical::CENTER;
		}

		inline void setDrawable(std::unique_ptr<DrawableAttr> drawable) {
			this->drawable.set(std::move(drawable));
			updateProperties();
		}

		inline void setDrawable(const DrawableKey& key) {
			this->drawable.set(std::make_unique<DrawableRef>(key));
			updateProperties();
		}

		inline void setDrawable(Drawable* drawable) {
			this->drawable.set(std::make_unique<DrawableValue>(drawable));
			updateProperties();
		}

		__declspec(property(put = setDrawable)) std::unique_ptr<DrawableAttr>& Drawable;

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

		__declspec(property(put = setTint)) std::unique_ptr<ColorAttr> Tint;

		inline void setScaleMode(ImageScaleMode mode) {
			this->scaleMode = mode;
		}

		__declspec(property(put = setScaleMode)) ImageScaleMode ScaleMode;

		inline void setGravity(const Alignment& gravity) {
			this->gravity = gravity;
		}

		__declspec(property(put = setGravity)) Alignment& Alignment;
	};
}