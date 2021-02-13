#pragma once

#include "core/SharedPointer.h"
#include "ui/control/SelectableView.h"
#include "ui/control/ImageView.h"
#include "ui/control/TextBlock.h"
#include "ui/layout/LinearLayout.h"
#include "ui/control/Space.h"
#include "ui/widget/Layout.h"
#include "ui/drawable/BitmapImage.h"
#include "ui/widget/StateIndicator.h"

namespace Ghurund::UI {
    class CheckBoxRadioLayout:public Ghurund::UI::WidgetLayout {
    protected:
        SelectableView* selectableView = nullptr;
        StateIndicator* stateIndicator = nullptr;
        ImageView* imageView = nullptr;
        EventHandler<Control> stateHandler = [this](Control& control) {
            if (selectableView->Pressed) {
                stateIndicator->State = IndicatorState::PRESSED;
            } else if (selectableView->Focused || selectableView->Hovered) {
                stateIndicator->State = IndicatorState::FOCUSED;
            } else {
                stateIndicator->State = IndicatorState::NONE;
            }
            return true;
        };

    public:
        CheckBoxRadioLayout(Control* layout) {
            Root = layout;
            selectableView = (Ghurund::UI::SelectableView*)layout->find("selectable");
            imageView = (Ghurund::UI::ImageView*)layout->find("image");
            stateIndicator = (Ghurund::UI::StateIndicator*)layout->find("state");
            selectableView->StateChanged.add(stateHandler);
        }

        ~CheckBoxRadioLayout() {
            if (selectableView)
                selectableView->StateChanged.remove(stateHandler);
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
        using CheckBoxRadioLayout::CheckBoxRadioLayout;

        virtual void onStateChanged(Control& control) override;
    };
}