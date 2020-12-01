#pragma once

#include "ObjectProperty.h"

#include "ui/Theme.h"
#include "ui/adapter/ItemAdapter.h"
#include "ui/control/TextBlock.h"
#include "ui/layout/LinearLayout.h"
#include "ui/widget/Separator.h"

namespace Ghurund::UI {
    class PropertyRow: public HorizontalLayout {
    private:
        SharedPointer<TextBlock> textView;
        SharedPointer<ControlContainer> container;

    public:
        PropertyRow(Theme& theme) {
            PreferredSize.height = PreferredSize::Height::WRAP;
            textView = ghnew TextBlock(theme.textViewSecondaryStyle);
            textView->PreferredSize.width = PreferredSize::Width::FILL;
            container = ghnew ControlContainer();
            container->PreferredSize.width = PreferredSize::Width::FILL;
            SeparatorPtr separator = ghnew Separator(ghnew VerticalSeparatorStyle(theme));
            Children = { textView, separator, container };
        }

        inline const String& getLabel() {
            return textView->Text;
        }

        inline void setLabel(const String& text) {
            textView->Text = text;
        }

        __declspec(property(get = getLabel, put = setLabel)) const String& Label;

        inline Control* getContent() {
            return container->Child;
        }

        inline void setContent(Control* control) {
            container->Child = control;
        }

        __declspec(property(get = getContent, put = setContent)) Control* Content;

        Event<PropertyRow> OnValueChanged = Event<PropertyRow>(*this);
    };

    class PropertyRowAdapter:public ItemAdapter<ObjectProperty*, PropertyRow> {
    private:
        Theme& theme;

    public:
        PropertyRowAdapter(Theme& theme):theme(theme) {}

        virtual PropertyRow* makeControl() const override {
            return ghnew PropertyRow(theme);
        }

        virtual void bind(PropertyRow& control, ObjectProperty* const& item, size_t position) const override {
            control.Label = item->Property.Name;
        }
    };
}