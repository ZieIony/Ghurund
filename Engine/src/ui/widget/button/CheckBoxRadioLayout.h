#pragma once

#include "core/ScopedPointer.h"
#include "ui/control/SelectableView.h"
#include "ui/control/ImageView.h"
#include "ui/control/TextBlock.h"
#include "ui/layout/LinearLayout.h"
#include "ui/control/Space.h"
#include "ui/widget/Layout.h"
#include "ui/drawable/BitmapImage.h"

namespace Ghurund::UI {
    class CheckBoxRadioLayout:public Ghurund::UI::Layout {
    protected:
        SelectableView* selectableView = nullptr;
        ImageView* imageView = nullptr;
        Theme& theme;

    public:
        CheckBoxRadioLayout(Theme& theme):theme(theme) {}

        ~CheckBoxRadioLayout() {
            if (selectableView)
                selectableView->release();
            if (imageView)
                imageView->release();
        }

        virtual void init() override;

        ImageView* getImageView() {
            return imageView;
        }

        __declspec(property(get = getImageView)) ImageView* ImageView;

        inline SelectableView* getSelectableView() {
            return selectableView;
        }

        __declspec(property(get = getSelectableView)) SelectableView* SelectableView;

        virtual void onStateChanged(Control& control) override;
    };

    class CheckBoxLayout:public CheckBoxRadioLayout {
    public:
        CheckBoxLayout(Theme& theme):CheckBoxRadioLayout(theme) {}

        virtual void onStateChanged(Control& control) override;
    };

    class RadioButtonLayout:public CheckBoxRadioLayout {
    public:
        RadioButtonLayout(Theme& theme):CheckBoxRadioLayout(theme) {}

        virtual void onStateChanged(Control& control) override;
    };

    class CheckBoxRadioTextLayout:public CheckBoxRadioLayout {
    protected:
        TextBlock* textView = nullptr;

    public:
        CheckBoxRadioTextLayout(Theme& theme):CheckBoxRadioLayout(theme) {}

        ~CheckBoxRadioTextLayout() {
            if (textView)
                textView->release();
        }

        virtual void init() override;

        TextBlock* getTextBlock() {
            return textView;
        }

        __declspec(property(get = getTextBlock)) TextBlock* TextBlock;

        virtual void onStateChanged(Control& control) override;
    };

    class TextCheckBoxLayout:public CheckBoxRadioTextLayout {
    public:
        TextCheckBoxLayout(Theme& theme):CheckBoxRadioTextLayout(theme) {}

        virtual void onStateChanged(Control& control) override;
    };

    class RadioTextButtonLayout:public CheckBoxRadioTextLayout {
    public:
        RadioTextButtonLayout(Theme& theme):CheckBoxRadioTextLayout(theme) {}

        virtual void onStateChanged(Control& control) override;
    };
}