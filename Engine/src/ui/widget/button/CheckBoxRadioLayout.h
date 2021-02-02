#pragma once

#include "core/SharedPointer.h"
#include "ui/control/SelectableView.h"
#include "ui/control/ImageView.h"
#include "ui/control/TextBlock.h"
#include "ui/layout/LinearLayout.h"
#include "ui/control/Space.h"
#include "ui/widget/Layout.h"
#include "ui/drawable/BitmapImage.h"

namespace Ghurund::UI {
    class CheckBoxRadioLayout:public Ghurund::UI::WidgetLayout {
    protected:
        SelectableView* selectableView = nullptr;
        ImageView* imageView = nullptr;

    public:
        CheckBoxRadioLayout() {}

        CheckBoxRadioLayout(Control* layout) {
            Root = layout;
            setPointer(selectableView, (Ghurund::UI::SelectableView*)layout->find("selectable"));
            setPointer(imageView, (Ghurund::UI::ImageView*)layout->find("image"));
        }

        ~CheckBoxRadioLayout() {
            if (selectableView)
                selectableView->release();
            if (imageView)
                imageView->release();
        }

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
        using CheckBoxRadioLayout::CheckBoxRadioLayout;

        virtual void onStateChanged(Control& control) override;
    };

    class RadioButtonLayout:public CheckBoxRadioLayout {
    public:
        virtual void onStateChanged(Control& control) override;
    };

    class CheckBoxRadioTextLayout:public CheckBoxRadioLayout {
    protected:
        TextBlock* textView = nullptr;

    public:
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
        virtual void onStateChanged(Control& control) override;
    };

    class RadioTextButtonLayout:public CheckBoxRadioTextLayout {
    public:
        virtual void onStateChanged(Control& control) override;
    };
}