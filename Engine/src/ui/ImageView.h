#pragma once

#include "Control.h"
#include "graphics/texture/Image.h"

namespace Ghurund {
    class ImageView {
    private:
        Image* image = nullptr;

    public:
        void setImage(Image* image) {
            setPointer(this->image, image);
        }

        Image* getImage() {
            return image;
        }

        __declspec(property(get = getImage, put = setImage)) Image* image;
    };
}