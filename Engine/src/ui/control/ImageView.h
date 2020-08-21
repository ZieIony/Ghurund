#pragma once

#include "Control.h"
#include "ui/layout/LayoutInflater.h"

#include <algorithm>
#include <objidl.h>
#include <gdiplus.h>

namespace Ghurund::UI {
    class ImageView : public Control {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(ImageView);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<ImageView>();

        GdiImage* image = nullptr;
        unsigned int tint = 0;

    public:
        ImageView(GdiImage* image = nullptr) {
            if (image) {
                image->addReference();
                this->image = image;
            }
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

        virtual void measure();

        virtual void draw(Canvas& canvas) override {
            if (!image)
                return;

            auto src = Gdiplus::RectF(0, 0, (float)image->image->GetWidth(), (float)image->image->GetHeight());
            auto dst = Gdiplus::RectF(0, 0, Size.x, Size.y);
            if (tint) {
                canvas.drawImage(*image, src, dst, tint);
            } else {
                canvas.drawImage(*image, src, dst);
            }
        }

        inline static const Ghurund::Type& TYPE = TypeBuilder<ImageView>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        static ImageView* inflate(LayoutInflater& inflater, json& json);
    };
}