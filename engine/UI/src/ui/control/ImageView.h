#pragma once

#include "core/Color.h"
#include "core/Colors.h"
#include "engine/graphics/texture/ITexture.h"
#include "ui/control/Control.h"
#include "ui/theme/ThemedValueProperty.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ImageView:public Control {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ImageView::GET_TYPE();
#pragma endregion

    private:
        // TODO: maybe this should be Image*?
        ThemedValueProperty<TextureKey, IntrusivePointer<ITexture>> image;
        TextureInput* imageInput = nullptr;
        ThemedValueProperty<ColorKey, Color> tint = Color(Colors::WHITE);
        Float4Input* tintInput = nullptr;

        inline void setThemedImage(std::unique_ptr<ThemedTexture> image) {
            if (!image) {
                setImage(IntrusivePointer<ITexture>());
            } else if (image->Key) {
                setImage(*image->Key);
            } else {
                setImage(image->Value);
            }
        }

        inline void setThemedTint(const ThemedColor& tint) {
            if (tint.Key) {
                setTint(*tint.Key);
            } else {
                setTint(tint.Value);
            }
        }

    protected:
        virtual void onMaterialChanged() override;

        virtual void onThemeChanged() override;

	public:
        inline void setImage(TextureKey image) {
            this->image.set(image);
            if (imageInput)
                imageInput->Value = this->image.get().get();
        }

        inline void setImage(IntrusivePointer<ITexture> image) {
            this->image.set(image);
            if (imageInput)
                imageInput->Value = this->image.get().get();
        }

        __declspec(property(put = setImage)) IntrusivePointer<ITexture> Image;

        inline void setTint(const ColorKey& tint) {
            this->tint = tint;
            auto theme = Theme;
            if (tintInput && theme) {
                this->tint.resolve(*theme);
                tintInput->Value = this->tint.get().toVector();
            }
        }

		inline void setTint(const Color& tint) {
			this->tint = tint;
			if (tintInput)
				tintInput->Value = tint.toVector();
		}

        __declspec(property(put = setTint)) const Color& Tint;
    };
}