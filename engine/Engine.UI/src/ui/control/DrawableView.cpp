#include "ghuipch.h"
#include "DrawableView.h"

#include "ui/Canvas.h"
#include "ui/loading/LayoutLoader.h"
#include "ui/theme/Theme.h"
#include "ui/drawable/InvalidImageDrawable.h"
#include "core/reflection/UniqueProperty.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& DrawableView::GET_TYPE() {
        static auto PROPERTY_DRAWABLE = UniqueProperty<DrawableView, std::unique_ptr<Ghurund::UI::DrawableAttr>>("Drawable", (void(DrawableView::*)(std::unique_ptr<Ghurund::UI::DrawableAttr>)) & setDrawable);
        static auto PROPERTY_TINT = UniqueProperty<DrawableView, std::unique_ptr<ColorAttr>>("Tint", (void(DrawableView::*)(std::unique_ptr<Ghurund::UI::ColorAttr>)) &setTint);
        static auto PROPERTY_SCALEMODE = Property<DrawableView, ImageScaleMode>("ScaleMode", &setScaleMode);

        static const auto CONSTRUCTOR = Constructor<DrawableView>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<DrawableView>(NAMESPACE_NAME, GH_STRINGIFY(DrawableView))
            .withProperty(PROPERTY_DRAWABLE)
            .withProperty(PROPERTY_SCALEMODE)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void DrawableView::onThemeChanged() {
        updateProperties();
    }

    void DrawableView::onMeasure() {
        const Ghurund::UI::Drawable* d = drawable.get();
        if (d) {
            measuredSize.Width = d->PreferredSize.Width;
            measuredSize.Height = d->PreferredSize.Height;
        } else {
            measuredSize = { 0, 0 };
        }
    }

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
        if (tint.get()) {
            drawable->draw(canvas, { dst.right - dst.left, dst.bottom - dst.top }, *tint.get());
        } else {
            drawable->draw(canvas, { dst.right - dst.left, dst.bottom - dst.top }, Color(0));
        }
        canvas.restore();
        canvas.restoreClipRect();
    }
}