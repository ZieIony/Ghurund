#pragma once

#include "Control.h"
#include "core/ScopedPointer.h"
#include "ui/Gravity.h"

#include <algorithm>
#include <objidl.h>
#include <gdiplus.h>

namespace Ghurund::UI {
    enum class ImageScaleMode {
        NONE, STRETCH, FIT, CROP
    };

    class ImageView: public Control {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ImageView);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<ImageView>();

        GdiImage* image = nullptr;
        unsigned int tint = 0;
        ImageScaleMode scaleMode = ImageScaleMode::CROP;
        Gravity gravity;

    public:
        ImageView(GdiImage* image = nullptr) {
            if (image) {
                image->addReference();
                this->image = image;
            }
            gravity.horizontal = Gravity::Horizontal::CENTER;
            gravity.vertical = Gravity::Vertical::CENTER;
        }

        ~ImageView() {
            if (image)
                image->release();
        }

        inline void setImage(GdiImage* image) {
            setPointer(this->image, image);
        }

        inline GdiImage* getImage() {
            return image;
        }

        __declspec(property(get = getImage, put = setImage)) GdiImage* Image;

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

        inline Gravity& getGravity() {
            return gravity;
        }

        inline void setGravity(const Gravity& gravity) {
            this->gravity = gravity;
        }

        __declspec(property(get = getGravity, put = setGravity)) Gravity& Gravity;

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onDraw(Canvas& canvas) override;

        inline static const Ghurund::Type& TYPE = TypeBuilder<ImageView>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<ImageView> ImageViewPtr;
}