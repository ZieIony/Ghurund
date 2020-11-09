#pragma once

#include "Control.h"
#include "core/ScopedPointer.h"
#include "ui/Alignment.h"
#include "ui/drawable/BitmapImage.h"

namespace Ghurund::UI {
    enum class ImageScaleMode {
        NONE, STRETCH, FIT, CROP
    };

    class ImageView: public Control {
    private:
        BitmapImage* image = nullptr;
        unsigned int tint = 0;
        ImageScaleMode scaleMode = ImageScaleMode::CROP;
        Alignment gravity;

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(ImageView))
                .withConstructor(NoArgsConstructor<ImageView>())
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    public:
        ImageView(BitmapImage* image = nullptr) {
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

        inline void setImage(BitmapImage* image) {
            setPointer(this->image, image);
        }

        inline BitmapImage* getImage() {
            return image;
        }

        __declspec(property(get = getImage, put = setImage)) BitmapImage* Image;

        inline void setTint(unsigned int color) {
            this->tint = color;
        }

        inline unsigned int getTint() {
            return tint;
        }

        __declspec(property(get = getTint, put = setTint)) unsigned int Tint;

        inline void setScaleMode(ImageScaleMode mode) {
            this->scaleMode = mode;
        }

        inline ImageScaleMode getScaleMode() const {
            return scaleMode;
        }

        __declspec(property(get = getScaleMode, put = setScaleMode)) ImageScaleMode ScaleMode;

        inline Alignment& getGravity() {
            return gravity;
        }

        inline void setGravity(const Alignment& gravity) {
            this->gravity = gravity;
        }

        __declspec(property(get = getGravity, put = setGravity)) Alignment& Alignment;

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onDraw(Canvas& canvas) override;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<ImageView> ImageViewPtr;
}