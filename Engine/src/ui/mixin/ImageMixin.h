#pragma once

#include "ui/control/ImageView.h"

namespace Ghurund::UI {
    class ImageMixin {
    protected:
        ImageView* imageView = nullptr;

    public:
        ImageDrawable* getImage() {
            return imageView->Image;
        }

        void setImage(ImageDrawable* image) {
            imageView->Image = image;
        }

        __declspec(property(get = getImage, put = setImage)) ImageDrawable* Image;
    };

    class ImageLayoutMixin {
    protected:
        ImageView* imageView;

    public:
        ImageLayoutMixin() {
            imageView = ghnew Ghurund::UI::ImageView();
        }

        ~ImageLayoutMixin() {
            imageView->release();
        }

        inline ImageView* getImageView() {
            return imageView;
        }

        __declspec(property(get = getImageView)) ImageView* ImageView;
    };
}