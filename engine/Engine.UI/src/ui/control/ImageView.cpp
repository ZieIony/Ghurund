#include "ghuipch.h"
#include "ImageView.h"

#include "ui/Canvas.h"
#include "ui/loading/LayoutLoader.h"
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
        measuredSize.Width = image ? (float)image->PreferredSize.Width : 0.0f;
        measuredSize.Height = image ? (float)image->PreferredSize.Height : 0.0f;
    }

    void ImageView::onDraw(ICanvas& canvas) {
        if (!image)
            return;

        auto src = FloatRect(0, 0, image->PreferredSize.Width, image->PreferredSize.Height);
        FloatRect dst;

        if (scaleMode == ImageScaleMode::NONE) {
            dst.left = (Size.Width - image->PreferredSize.Width) / 2.0f;
            dst.top = (Size.Height - image->PreferredSize.Height) / 2.0f;
            dst.right = dst.left + image->PreferredSize.Width;
            dst.bottom = dst.top + image->PreferredSize.Height;
        } else if (scaleMode == ImageScaleMode::STRETCH) {
            dst.left = 0;
            dst.top = 0;
            dst.right = Size.Width;
            dst.bottom = Size.Height;
        } else if (scaleMode == ImageScaleMode::FIT) {
            float sx = Size.Width / image->PreferredSize.Width;
            float sy = Size.Height / image->PreferredSize.Height;
            float s = std::min(sx, sy);
            float width = image->PreferredSize.Width * s;
            float height = image->PreferredSize.Height * s;
            if (gravity.horizontal == Alignment::Horizontal::LEFT) {
                dst.left = 0;
            } else if (gravity.horizontal == Alignment::Horizontal::CENTER) {
                dst.left = (Size.Width - width) / 2.0f;
            } else {
                dst.left = Size.Width - width;
            }
            if (gravity.vertical == Alignment::Vertical::TOP) {
                dst.top = 0;
            } else if (gravity.vertical == Alignment::Vertical::CENTER) {
                dst.top = (Size.Height - height) / 2.0f;
            } else {
                dst.top = Size.Height - height;
            }
            dst.right = dst.left + width;
            dst.bottom = dst.top + height;
        } else if (scaleMode == ImageScaleMode::CROP) {
            float sx = Size.Width / image->PreferredSize.Width;
            float sy = Size.Height / image->PreferredSize.Height;
            float s = std::max(sx, sy);
            float width = image->PreferredSize.Width * s;
            float height = image->PreferredSize.Height * s;
            if (gravity.horizontal == Alignment::Horizontal::LEFT) {
                dst.left = 0;
            } else if (gravity.horizontal == Alignment::Horizontal::CENTER) {
                dst.left = (Size.Width - width) / 2.0f;
            } else {
                dst.left = Size.Width - width;
            }
            if (gravity.vertical == Alignment::Vertical::TOP) {
                dst.top = 0;
            } else if (gravity.vertical == Alignment::Vertical::TOP) {
                dst.top = (Size.Height - height) / 2.0f;
            } else {
                dst.top = Size.Height - height;
            }
            dst.right = dst.left + width;
            dst.bottom = dst.top + height;
        }

        image->Size = { dst.right - dst.left, dst.bottom - dst.top };
        canvas.clipRect(0, 0, Size.Width, Size.Height);
        canvas.save();
        canvas.translate(dst.left, dst.top);
        if (Tint)
            image->Tint = Tint->getValue(*this);
        image->draw(canvas);
        canvas.restore();
        canvas.restoreClipRect();
    }

    void ImageView::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        __super::load(loader, xml);
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