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

        Gdiplus::Image* image = nullptr;

    public:
        ImageView(Gdiplus::Image* image = nullptr) {
            this->image = image;
        }

        ~ImageView() {
            delete image;
        }

        inline void setImage(Gdiplus::Image* image) {
            this->image = image;
        }

        inline Gdiplus::Image* getImage() {
            return image;
        }

        __declspec(property(get = getImage, put = setImage)) Gdiplus::Image* Image;

        Paint paint;
        virtual void draw(Canvas& canvas) override {
            if (image)
                canvas.drawImage(*image, 0, 0, Size.x, Size.y);
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