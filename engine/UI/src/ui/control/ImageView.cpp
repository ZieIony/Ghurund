#include "ghuipch.h"
#include "ImageView.h"

#include "core/reflection/Property.h"
#include "core/reflection/UniqueProperty.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& ImageView::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<ImageView>();
		static auto PROPERTY_IMAGE = UniqueProperty<ImageView, std::unique_ptr<ThemedTexture>>("Image", &setThemedImage);
		static auto PROPERTY_TINT = Property<ImageView, const ThemedColor&>("Tint", &setThemedTint);

		static const Ghurund::Core::Type TYPE = TypeBuilder<ImageView>()
			.withConstructor(CONSTRUCTOR)
			.withProperty(PROPERTY_IMAGE)
			.withProperty(PROPERTY_TINT)
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

    void ImageView::onMaterialChanged() {
        __super::onMaterialChanged();
        if (material != nullptr) {
            imageInput = (TextureInput*)material->Inputs.get("image");
            imageInput->Value = image.get().get();
            tintInput = (Float4Input*)material->Inputs.get("tint");
            tintInput->Value = tint.get().toVector();
        } else {
            imageInput = nullptr;
            tintInput = nullptr;
        }
    }

    void ImageView::onThemeChanged() {
        __super::onThemeChanged();
        auto theme = Theme;
        if (theme) {
            image.resolve(*theme);
            if (imageInput)
                imageInput->Value = image.get().get();
        }
    }
}