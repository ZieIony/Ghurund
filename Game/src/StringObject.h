#pragma once

#include "core/SharedPointer.h"
#include "core/string/String.h"
#include "ui/adapter/RecyclerView.h"
#include "ui/control/Clip.h"
#include "ui/control/ColorView.h"
#include "ui/control/PaddingContainer.h"
#include "ui/control/TextBlock.h"
#include "ui/drawable/BitmapImageDrawable.h"
#include "ui/layout/LinearLayout.h"
#include "ui/layout/StackLayout.h"
#include "ui/widget/ClickResponseView.h"
#include "ui/widget/button/Button.h"
#include "ui/style/Theme.h"

using namespace Ghurund;
using namespace Ghurund::UI;

enum class StringObjectType {
    ITEM, HEADER
};

namespace Game {
    struct StringObject {
        StringObjectType type;

        virtual ~StringObject() {}
    };

    struct StringObjectItem:public StringObject {
        Ghurund::WString text, subtext;
        BitmapImage* image;

        StringObjectItem(const Ghurund::WString& text, const Ghurund::WString& subtext, BitmapImage* image):text(text), subtext(subtext) {
            this->image = image;
            if (image)
                image->addReference();
            type = StringObjectType::ITEM;
        }

        ~StringObjectItem() {
            image->release();
        }
    };

    struct StringObjectHeader:public StringObject {
        Ghurund::WString text;

        StringObjectHeader(const Ghurund::WString& text):text(text) {
            type = StringObjectType::HEADER;
        }
    };

    class StringObjectHeaderRow:public StackLayout {
    private:
        SharedPointer<TextBlock> tv;
        SharedPointer<PaddingContainer> padding;

    public:
        StringObjectHeaderRow(Ghurund::UI::Theme& theme) {
            preferredSize.height = PreferredSize::Height::WRAP;

            padding = ghnew PaddingContainer();
            {
                padding->PreferredSize.width = PreferredSize::Width::FILL;
                padding->Padding = { 16.0f, 4.0f };

                tv = ghnew TextBlock();
                tv->Style = theme.Styles[Theme::STYLE_TEXTBLOCK_HEADER];
                tv->PreferredSize.width = PreferredSize::Width::FILL;
                padding->Child = tv;

            }
            ColorView* colorView = ghnew ColorView(theme.Colors[Theme::COLOR_BACKGR0UND]);
            Children = {
                colorView,
                padding
            };
            colorView->release();
        }

        const Ghurund::WString& getText() {
            return tv->Text;
        }

        void setText(const Ghurund::WString& text) {
            tv->Text = text;
        }

        __declspec(property(get = getText, put = setText)) const WString& Text;
    };

    class StringHeaderAdapter:public ItemAdapter<StringObject*, Control> {
    private:
        Theme& theme;

    public:
        StringHeaderAdapter(Theme& theme):theme(theme) {}

        virtual bool canHandleItem(StringObject* const& item, size_t position) const override {
            return item->type == StringObjectType::HEADER;
        }

        virtual Control* makeControl() const override {
            return ghnew StringObjectHeaderRow(theme);
        }

        virtual void bind(Control& control, StringObject* const& item, size_t position) const override {
            StringObjectHeaderRow& sor = (StringObjectHeaderRow&)control;
            StringObjectHeader* strObj = (StringObjectHeader*)item;
            sor.Text = strObj->text;
        }
    };
}
