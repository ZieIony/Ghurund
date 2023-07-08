#include "ghuipch.h"
#include "DrawableView.h"

#include "ui/Canvas.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/style/Theme.h"
#include "ui/drawable/InvalidImageDrawable.h"

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::ImageScaleMode>() {
        static Type TYPE = Type("ImageScaleMode", sizeof(Ghurund::UI::ImageScaleMode));
        return TYPE;
    }
}

namespace Ghurund::UI {
    const Ghurund::Core::Type& DrawableView::GET_TYPE() {
        static auto PROPERTY_IMAGE = Property<DrawableView, std::unique_ptr<Ghurund::UI::DrawableAttr>&>("Drawable", & setDrawable);
        //static auto PROPERTY_TINT = Property<DrawableView, std::unique_ptr<ColorAttr>>("Tint", &getTint, &setTint);
        static auto PROPERTY_SCALEMODE = Property<DrawableView, ImageScaleMode>("ScaleMode", &setScaleMode);

        static const auto CONSTRUCTOR = Constructor<DrawableView>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<DrawableView>(NAMESPACE_NAME, GH_STRINGIFY(DrawableView))
            .withProperty(PROPERTY_IMAGE)
            .withProperty(PROPERTY_SCALEMODE)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void DrawableView::onThemeChanged() {
        const UI::Theme* theme = Theme;
        if (theme) {
            tint.resolve(*theme);
            drawable.resolve(*theme);
        }
    }

    /*void DrawableView::onMeasure(float parentWidth, float parentHeight) {
        measuredSize.Width = drawable ? (float)drawable->PreferredSize.Width : 0.0f;
        measuredSize.Height = drawable ? (float)drawable->PreferredSize.Height : 0.0f;
    }*/

    void DrawableView::onDraw(ICanvas& canvas) {
        auto drawable = this->drawable.get();
        if (!drawable)
            return;

        auto src = FloatRect(0, 0, drawable->PreferredSize.Width, drawable->PreferredSize.Height);
        FloatRect dst;

        if (scaleMode == ImageScaleMode::NONE) {
            dst.left = (Size.Width - drawable->PreferredSize.Width) / 2.0f;
            dst.top = (Size.Height - drawable->PreferredSize.Height) / 2.0f;
            dst.right = dst.left + drawable->PreferredSize.Width;
            dst.bottom = dst.top + drawable->PreferredSize.Height;
        } else if (scaleMode == ImageScaleMode::STRETCH) {
            dst.left = 0;
            dst.top = 0;
            dst.right = Size.Width;
            dst.bottom = Size.Height;
        } else if (scaleMode == ImageScaleMode::FIT) {
            float sx = Size.Width / drawable->PreferredSize.Width;
            float sy = Size.Height / drawable->PreferredSize.Height;
            float s = std::min(sx, sy);
            float width = drawable->PreferredSize.Width * s;
            float height = drawable->PreferredSize.Height * s;
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
            float sx = Size.Width / drawable->PreferredSize.Width;
            float sy = Size.Height / drawable->PreferredSize.Height;
            float s = std::max(sx, sy);
            float width = drawable->PreferredSize.Width * s;
            float height = drawable->PreferredSize.Height * s;
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

        canvas.clipRect(0, 0, Size.Width, Size.Height);
        canvas.save();
        canvas.translate(dst.left, dst.top);
        //if (tint.get())
            //drawable->Tint = *tint.get();
        drawable->draw(canvas, { dst.right - dst.left, dst.bottom - dst.top });
        canvas.restore();
        canvas.restoreClipRect();
    }

    void DrawableViewStyle::onStateChanged(Control& control) const {
        DrawableView& drawableView = ((DrawableView&)control);
        /*if (control.Enabled) {
            drawableView.Alpha = 1.0f;
        } else {
            drawableView.Alpha = 0.38f;
        }*/
    }

    void DrawableViewOnBackgroundStyle::onStateChanged(Control& control) const {
        DrawableView& drawableView = ((DrawableView&)control);
        if (control.Enabled) {
            drawableView.Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_PRIMARY_ONBACKGROUND));
        } else {
            drawableView.Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND));
        }
    }

    void DrawableViewOnAccentStyle::onStateChanged(Control& control) const {
        DrawableView& drawableView = ((DrawableView&)control);
        if (control.Enabled) {
            drawableView.Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_PRIMARY_ONACCENT));
        } else {
            drawableView.Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_DISABLED_ONACCENT));
        }
    }

    void DrawableViewAccentStyle::onStateChanged(Control& control) const {
        DrawableView& drawableView = ((DrawableView&)control);
        if (control.Enabled) {
            drawableView.Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_ACCENT));
        } else {
            drawableView.Tint = std::unique_ptr<ColorAttr>(ghnew ColorRef(Theme::COLOR_DISABLED_ONBACKGROUND));
        }
    }
}