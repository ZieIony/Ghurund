#pragma once

#include "ObjectProperty.h"

#include "core/string/TextConversionUtils.h"
#include "ui/adapter/ItemAdapter.h"
#include "ui/text/TextBlock.h"
#include "ui/theme/Theme.h"
#include "ui/widget/Separator.h"

namespace Ghurund::UI {
    class PropertyRow: public HorizontalLayout {
    private:
        IntrusivePointer<TextBlock> textView;
        IntrusivePointer<ControlContainer> container;

    public:
        PropertyRow() {
            ContentSize.height = ContentSize::Height::WRAP;
            textView = ghnew TextBlock();
            textView->ContentSize.width = ContentSize::Width::FILL;
            container = ghnew ControlContainer();
            container->ContentSize.width = ContentSize::Width::FILL;
            auto separator = makeIntrusive<Separator>();
            //separator->Style = theme.Styles[Theme::STYLE_SEPARATOR_VERTICAL];
            Children = { textView, separator, container };
        }

        inline const WString& getLabel() {
            return textView->Text;
        }

        inline void setLabel(const WString& text) {
            textView->Text = text;
        }

        __declspec(property(get = getLabel, put = setLabel)) const WString& Label;

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
    public:
        virtual PropertyRow* makeControl() const override {
            return ghnew PropertyRow();
        }

        virtual void bind(PropertyRow& control, ObjectProperty* const& item, size_t position) const override {
            control.Label = convertText(AString(item->Property.Name));
        }
    };
}