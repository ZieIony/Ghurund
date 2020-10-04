#pragma once

#include "ui/control/ImageView.h"

namespace Ghurund::UI {
    class ImageMixin {
    protected:
        ImageView* imageView = nullptr;

    public:
        const GdiImage* getImage() const {
            return imageView->Image;
        }

        void setImage(GdiImage* image) {
            imageView->Image = image;
        }

        __declspec(property(get = getImage, put = setImage)) GdiImage* Image;

        inline void setImageTint(unsigned int color) {
            imageView->Tint = color;
        }

        inline unsigned int getImageTint() {
            return imageView->Tint;
        }

        __declspec(property(get = getImageTint, put = setImageTint)) unsigned int ImageTint;
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