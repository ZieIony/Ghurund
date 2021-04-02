#pragma once

#include "PropertyRow.h"
#include "ui/widget/text/TextField.h"

namespace Ghurund::UI {
    template<class StringType>
    class StringPropertyRow: public PropertyRow {
    private:
        SharedPointer<TextField> textField;

    public:
        StringPropertyRow() {
            textField = ghnew TextField();
            textField->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::WRAP };
            textField->OnTextChanged.add([this](TextField& textField) {
                return OnValueChanged();
            });
            Content = textField;
        }

        inline const StringType& getValue() {
            return textField->Text;
        }

        inline void setValue(const StringType& text) {
            textField->Text = text;
        }

        __declspec(property(get = getValue, put = setValue)) const StringType& Value;
    };

    template<class StringType>
    class StringPropertyRowAdapter:public ItemAdapter<ObjectProperty*, PropertyRow> {
    public:
        virtual PropertyRow* makeControl() const override {
            return ghnew StringPropertyRow<StringType>();
        }

        virtual void bind(PropertyRow& control, ObjectProperty* const& item, size_t position) const override {
            control.Label = toWideChar(AString(item->Property.Name));
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

    class WStringPropertyRowAdapter:public StringPropertyRowAdapter<WString> {
    public:
        virtual bool canHandleItem(ObjectProperty* const& item, size_t position) const override {
            return strcmp("WString", item->Property.TypeName) == 0;
        }
    };

    class AStringPropertyRowAdapter:public StringPropertyRowAdapter<WString> {
    public:
        virtual bool canHandleItem(ObjectProperty* const& item, size_t position) const override {
            return strcmp("AString", item->Property.TypeName) == 0;
        }
    };
}