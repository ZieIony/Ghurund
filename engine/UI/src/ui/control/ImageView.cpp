#include "ghuipch.h"
#include "ImageView.h"

#include "core/reflection/Property.h"
#include "core/reflection/UniqueProperty.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& ImageView::GET_TYPE() {
		static const auto CONSTRUCTOR = Constructor<ImageView>();
		static auto PROPERTY_IMAGE = UniqueProperty<ImageView, std::unique_ptr<TextureAttr>>("Image", &setImage);
		static auto PROPERTY_TINT = Property<ImageView, const Color&>("Tint", &getTint, &setTint);

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
            imageParameter = (TextureParameter*)material->Parameters.get("image");
            imageParameter->Value = image.get();
            tintParameter = (Float4Parameter*)material->Parameters.get("tint");
            tintParameter->Value = tint.toVector();
        } else {
            imageParameter = nullptr;
            tintParameter = nullptr;
        }
    }

    void ImageView::onThemeChanged() {
        const UI::Theme* theme = Theme;
        if (theme) {
            image.resolve(*theme);
            if (imageParameter)
                imageParameter->Value = image.get();
        }
    }
}