#include "ghuipch.h"
#include "ImageView.h"

#include "ui/Canvas.h"
#include "ui/layout/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/drawable/InvalidImageDrawable.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& ImageView::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ImageView>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<ImageView>(NAMESPACE_NAME, GH_STRINGIFY(ImageView))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void ImageView::onMeasure(float parentWidth, float parentHeight) {
        measuredSize.width = std::max(minSize.width, (float)preferredSize.width);
        measuredSize.width = std::max(measuredSize.width, image ? (float)image->PreferredSize.width : 0.0f);
        measuredSize.height = std::max(minSize.height, (float)preferredSize.height);
        measuredSize.height = std::max(measuredSize.height, image ? (float)image->PreferredSize.height : 0.0f);
    }

    void ImageView::onDraw(Canvas& canvas) {
        if (!image)
            return;

        auto src = FloatRect(0, 0, (float)image->PreferredSize.width, (float)image->PreferredSize.height);
        FloatRect dst;

        if (scaleMode == ImageScaleMode::NONE) {
            dst.left = (Size.width - image->PreferredSize.width) / 2.0f;
            dst.top = (Size.height - image->PreferredSize.height) / 2.0f;
            dst.right = dst.left + image->PreferredSize.width;
            dst.bottom = dst.top + image->PreferredSize.height;
        } else if (scaleMode == ImageScaleMode::STRETCH) {
            dst.left = 0;
            dst.top = 0;
            dst.right = Size.width;
            dst.bottom = Size.height;
        } else if (scaleMode == ImageScaleMode::FIT) {
            float sx = Size.width / image->PreferredSize.width;
            float sy = Size.height / image->PreferredSize.height;
            float s = std::min(sx, sy);
            float width = image->PreferredSize.width * s;
            float height = image->PreferredSize.height * s;
            if (gravity.horizontal == Alignment::Horizontal::LEFT) {
                dst.left = 0;
            } else if (gravity.horizontal == Alignment::Horizontal::CENTER) {
                dst.left = (Size.width - width) / 2.0f;
            } else {
                dst.left = Size.width - width;
            }
            if (gravity.vertical == Alignment::Vertical::TOP) {
                dst.top = 0;
            } else if (gravity.vertical == Alignment::Vertical::CENTER) {
                dst.top = (Size.height - height) / 2.0f;
            } else {
                dst.top = Size.height - height;
            }
            dst.right = dst.left + width;
            dst.bottom = dst.top + height;
        } else if (scaleMode == ImageScaleMode::CROP) {
            float sx = Size.width / image->PreferredSize.width;
            float sy = Size.height / image->PreferredSize.height;
            float s = std::max(sx, sy);
            float width = image->PreferredSize.width * s;
            float height = image->PreferredSize.height * s;
            if (gravity.horizontal == Alignment::Horizontal::LEFT) {
                dst.left = 0;
            } else if (gravity.horizontal == Alignment::Horizontal::CENTER) {
                dst.left = (Size.width - width) / 2.0f;
            } else {
                dst.left = Size.width - width;
            }
            if (gravity.vertical == Alignment::Vertical::TOP) {
                dst.top = 0;
            } else if (gravity.vertical == Alignment::Vertical::TOP) {
                dst.top = (Size.height - height) / 2.0f;
            } else {
                dst.top = Size.height - height;
            }
            dst.right = dst.left + width;
            dst.bottom = dst.top + height;
        }

        image->Size = { dst.right - dst.left, dst.bottom - dst.top };
        canvas.clipRect(0, 0, Size.width, Size.height);
        canvas.save();
        canvas.translate(dst.left, dst.top);
        if (Tint)
            image->Tint = Tint->getValue(*this);
        image->draw(canvas);
        canvas.restore();
        canvas.restoreClipRect();
    }

    Status ImageView::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        Status result = __super::load(loader, xml);
        if (result != Status::OK)
            return result;
        auto imageAttr = xml.FindAttribute("image");
        if (imageAttr) {
            SharedPointer<ImageDrawable> image = loader.loadDrawable(imageAttr->Value());
            if (!image)
                image = ghnew InvalidImageDrawable();
            Image = image;
        }
        if (this->image) {
            auto imageTintAttr = xml.FindAttribute("imageTint");
            if (imageTintAttr)
                Tint = std::unique_ptr<ColorAttr>(loader.loadColor(imageTintAttr->Value()));
        }
        return Status::OK;
    }

    void ImageViewStyle::onStateChanged(Control& control) const {
        ImageView& imageView = ((ImageView&)control);
        if (!imageView.Image)
            return;
        if (control.Enabled) {
            imageView.Image->Alpha = 1.0f;
        } else {
            imageView.Image->Alpha = 0.38f;
        }
    }

    void ImageViewOnBackgroundStyle::onStateChanged(Control& control) const {
        ImageView& imageView = ((ImageView&)control);
        if (control.Enabled) {
            imageView.Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND));
        } else {
            imageView.Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND));
        }
    }

    void ImageViewOnAccentStyle::onStateChanged(Control& control) const {
        ImageView& imageView = ((ImageView&)control);
        if (control.Enabled) {
            imageView.Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_PRIMARY_ONACCENT));
        } else {
            imageView.Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_DISABLED_ONACCENT));
        }
    }

    void ImageViewAccentStyle::onStateChanged(Control& control) const {
        ImageView& imageView = ((ImageView&)control);
        if (control.Enabled) {
            imageView.Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_ACCENT));
        } else {
            imageView.Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND));
        }
    }
}