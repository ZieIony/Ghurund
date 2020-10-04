#pragma once

#include "ClickableView.h"

namespace Ghurund::UI {
    class SelectableView:public ClickableView {
    private:
        bool selected = false;

    public:
        inline bool isSelected() const {
            return selected;
        }

        inline void setSelected(bool selected) {
            this->selected = selected;
            invalidateCache();
            onStateChanged();
        }

        __declspec(property(get = isSelected, put = setSelected)) bool Selected;

    private:
        inline static const Property& SELECTED = TypedProperty<SelectableView, bool>(
            GH_STRINGIFY(bool), "selected", &isSelected, &setSelected);
    };
}