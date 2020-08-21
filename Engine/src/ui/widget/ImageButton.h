#pragma once

#include "Button.h"
#include "ui/control/Stack.h"
#include "ui/control/ImageView.h"
#include "ui/control/Border.h"
#include "ui/control/Surface.h"
#include "ui/control/Clip.h"

namespace Ghurund::UI {
    class ImageButton :public Button {
    private:
        ImageView* imageView;

    public:
        ImageButton() {
            imageView = ghnew ImageView();
            imageView->setPreferredSize(PreferredSize::Width::WRAP, PreferredSize::Height::WRAP);
            Content = imageView;
        }

        ImageButton(GdiImage* image):ImageButton() {
            Image = image;
        }

        ~ImageButton() {
            imageView->release();
        }

        inline void setImage(GdiImage* image) {
            imageView->Image = image;
        }

        inline GdiImage* getImage() {
            return imageView->Image;
        }

        __declspec(property(get = getImage, put = setImage)) GdiImage* Image;

        virtual void measure() {
            imageView->PreferredSize = PreferredSize;
            __super::measure();
        }
    };
}