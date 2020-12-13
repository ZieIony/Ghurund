#pragma once

#include "PropertyRow.h"
#include "ui/widget/textfield/TextField.h"

namespace Ghurund::UI {
    template<class StringType>
    class StringPropertyRow: public PropertyRow {
    private:
        TextFieldPtr textField;

    public:
        StringPropertyRow() {
            textField = ghnew TextField();
            textField->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::WRAP };
            textField->OnTextChanged.add([this](TextField& textField) {
                return OnValueChanged();
            });
            Content = textField;
        }

        inline StringType& getValue() {
            return textField->Text;
        }

        inline void setValue(StringType& text) {
            textField->Text = text;
        }

        __declspec(property(get = getValue, put = setValue)) StringType& Value;
    };

    template<class StringType>
    class StringPropertyRowAdapter:public ItemAdapter<ObjectProperty*, PropertyRow> {
    public:
        virtual PropertyRow* makeControl() const override {
            return ghnew StringPropertyRow<StringType>();
        }

        virtual void bind(PropertyRow& control, ObjectProperty* const& item, size_t position) const override {
            control.Label = item->Property.Name;
            StringType b;
            item->get((void**)&b);
            ((StringPropertyRow<StringType>&)control).Value = b;
            control.Content->Enabled = !item->Property.ReadOnly;
            control.OnValueChanged.clear();
            if (!item->Property.ReadOnly) {
                control.OnValueChanged.add([item](PropertyRow& row) {
                    StringType b = ((StringPropertyRow<StringType>&)row).Value;
                    item->set(*(void**)&b);
                    row.repaint();
                    return true;
                });
            }
        }
    };

    class UnicodeStringPropertyRowAdapter:public StringPropertyRowAdapter<UnicodeString> {
    public:
        virtual bool canHandleItem(ObjectProperty* const& item, size_t position) const override {
            return strcmp("UnicodeString", item->Property.TypeName) == 0;
        }
    };

    class ASCIIStringPropertyRowAdapter:public StringPropertyRowAdapter<UnicodeString> {
    public:
        virtual bool canHandleItem(ObjectProperty* const& item, size_t position) const override {
            return strcmp("ASCIIString", item->Property.TypeName) == 0;
        }
    };
}