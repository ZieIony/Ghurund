#pragma once

#include "Control.h"
#include "core/SharedPointer.h"
#include "ui/Alignment.h"
#include "ui/drawable/Drawable.h"
#include <ui/drawable/BitmapImageDrawable.h>

namespace Ghurund::UI {
    enum class ImageScaleMode {
        NONE, STRETCH, FIT, CROP
    };

    class ImageView: public Control {
    private:
        ImageDrawable* image = nullptr;
        ImageScaleMode scaleMode = ImageScaleMode::CROP;
        Alignment gravity;

    protected:
        static const Ghurund::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = NoArgsConstructor<ImageView>();
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ImageView))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        ImageView(ImageDrawable* image = nullptr) {
            if (image) {
                image->addReference();
                this->image = image;
            }
            gravity.horizontal = Alignment::Horizontal::CENTER;
            gravity.vertical = Alignment::Vertical::CENTER;
        }

        ~ImageView() {
            if (image)
                image->release();
        }

        inline void setImage(ImageDrawable* image) {
            setPointer(this->image, image);
        }

        inline ImageDrawable* getImage() {
            return image;
        }

        __declspec(property(get = getImage, put = setImage)) ImageDrawable* Image;

        inline void setScaleMode(ImageScaleMode mode) {
            this->scaleMode = mode;
        }

        inline ImageScaleMode getScaleMode() const {
            return scaleMode;
        }

        __declspec(property(get = getScaleMode, put = setScaleMode)) ImageScaleMode ScaleMode;

        inline const Alignment& getGravity() const {
            return gravity;
        }

        inline void setGravity(const Alignment& gravity) {
            this->gravity = gravity;
        }

        __declspec(property(get = getGravity, put = setGravity)) Alignment& Alignment;

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onDraw(Canvas& canvas) override;

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    class ImageViewStyle:public Style {
    public:
        void onStateChanged(Control& control) const;
    };

    class ImageViewOnBackgroundStyle:public Style {
    public:
        void onStateChanged(Control& control) const;
    };

    class ImageViewOnAccentStyle:public Style {
    public:
        void onStateChanged(Control& control) const;
    };

    class ImageViewAccentStyle:public Style {
    public:
        void onStateChanged(Control& control) const;
    };
}