#pragma once

#include "Control.h"
#include "ui/Alignment.h"
#include "ui/drawable/ImageDrawable.h"
#include "ui/style/PointerAttrProperty.h"
#include "ui/style/AttrProperty.h"
#include "ui/style/ColorAttr.h"
#include "ui/style/DrawableAttr.h"

namespace Ghurund::UI {
    enum class ImageScaleMode {
        NONE, STRETCH, FIT, CROP
    };
}

namespace Ghurund::Core {
    template<>
    const Type& getType<Ghurund::UI::ImageScaleMode>();
}

namespace Ghurund::UI{
    class DrawableView: public Control {
    private:
        PointerAttrProperty<DrawableAttr, Drawable> drawable;
        NullableAttrProperty<ColorAttr, Color> tint;
        ImageScaleMode scaleMode = ImageScaleMode::CROP;
        Alignment gravity;

    protected:
        //virtual void onMeasure(float parentWidth, float parentHeight) override;

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

        inline void setDrawable(std::unique_ptr<DrawableAttr>& drawable) {
            this->drawable.set(std::move(drawable));
        }

        __declspec(property(put = setDrawable)) std::unique_ptr<DrawableAttr>& Drawable;

        inline void setTint(std::unique_ptr<ColorAttr> tint) {
            this->tint.set(std::move(tint));
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

        virtual void onThemeChanged() override;
    };

    class DrawableViewStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };

    class DrawableViewOnBackgroundStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };

    class DrawableViewOnAccentStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };

    class DrawableViewAccentStyle:public Style {
    public:
        virtual void onStateChanged(Control& control) const override;
    };
}