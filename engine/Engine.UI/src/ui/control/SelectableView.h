#pragma once

#include "ClickableControl.h"

namespace Ghurund::UI {
    class SelectableView:public ClickableControl {
    private:
        bool selected = false;

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline bool isSelected() const {
            return selected;
        }

        inline void setSelected(bool selected) {
            this->selected = selected;
            onStateChanged();
        }

        __declspec(property(get = isSelected, put = setSelected)) bool Selected;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;

    private:
        //inline static const TypeProperty& SELECTED = TypedProperty<SelectableView, bool>(
         //   GH_STRINGIFY(bool), "selected", &isSelected, &setSelected);
    };
}