#pragma once

#include "PropertyRow.h"
#include "ui/widget/TextField.h"

namespace Ghurund::UI {
    class StringPropertyRow: public PropertyRow {
    private:
        TextFieldPtr textField;

    public:
        StringPropertyRow(Theme& theme):PropertyRow(theme) {
            textField = ghnew TextField(theme);
            textField->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::WRAP };
            textField->OnTextChanged.add([this](TextField& textField) {
                return OnValueChanged();
            });
            Content = textField;
        }

        inline UnicodeString& getValue() {
            return textField->Text;
        }

        inline void setValue(UnicodeString& text) {
            textField->Text = text;
        }

        __declspec(property(get = getValue, put = setValue)) UnicodeString& Value;
    };

    class StringPropertyRowAdapter:public ItemAdapter<ObjectProperty*, PropertyRow> {
    private:
        Theme& theme;

    public:
        StringPropertyRowAdapter(Theme& theme):theme(theme) {}

        virtual bool canHandleItem(ObjectProperty* const& item, size_t position) const override {
            return S("String") == item->Property.TypeName;
        }

        virtual PropertyRow* makeControl() const override {
            return ghnew StringPropertyRow(theme);
        }

        virtual void bind(PropertyRow& control, ObjectProperty* const& item, size_t position) const override {
            control.Label = item->Property.Name;
            UnicodeString b;
            item->get((void**)&b);
            ((StringPropertyRow&)control).Value = b;
            control.Content->Enabled = !item->Property.ReadOnly;
            control.OnValueChanged.clear();
            if (!item->Property.ReadOnly) {
                control.OnValueChanged.add([item](PropertyRow& row) {
                    String b = ((StringPropertyRow&)row).Value;
                    item->set(*(void**)&b);
                    row.repaint();
                    return true;
                });
            }
        }
    };
}