#pragma once

#include "MaterialColors.h"

#include "core/ScopedPointer.h"
#include "core/string/String.h"
#include "ui/adapter/RecyclerView.h"
#include "ui/control/Clip.h"
#include "ui/control/ColorView.h"
#include "ui/control/PaddingContainer.h"
#include "ui/control/TextBlock.h"
#include "ui/drawable/BitmapImage.h"
#include "ui/layout/LinearLayout.h"
#include "ui/widget/ClickResponseView.h"

using namespace Ghurund;
using namespace Ghurund::UI;

enum class StringObjectType {
    ITEM, HEADER
};

struct StringObject {
    StringObjectType type;

    virtual ~StringObject() {}
};

struct StringObjectItem:public StringObject {
    Ghurund::String text, subtext;
    BitmapImage* image;

    StringObjectItem(const Ghurund::String& text, const Ghurund::String& subtext, BitmapImage* image):text(text), subtext(subtext) {
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
    Ghurund::String text;

    StringObjectHeader(const Ghurund::String& text):text(text) {
        type = StringObjectType::HEADER;
    }
};

class StringObjectHeaderRow:public StackLayout {
private:
    ScopedPointer<TextBlock> tv;
    ScopedPointer<PaddingContainer> padding;

public:
    StringObjectHeaderRow(Theme& theme) {
        preferredSize.height = PreferredSize::Height::WRAP;

        padding = ghnew PaddingContainer();
        {
            padding->PreferredSize.width = PreferredSize::Width::FILL;
            padding->Padding.Horizontal = 16.0f;
            padding->Padding.Vertical = 4.0f;

            tv = ghnew TextBlock(theme.textViewHeaderStyle);
            tv->PreferredSize.width = PreferredSize::Width::FILL;
            padding->Child = tv;

        }
        ColorView* colorView = ghnew ColorView(theme.getColorBackground());
        Children = {
            colorView,
            padding
        };
        colorView->release();
    }

    Ghurund::UnicodeString& getText() {
        return tv->Text;
    }

    void setText(const Ghurund::UnicodeString& text) {
        tv->Text = text;
    }

    __declspec(property(get = getText, put = setText)) const UnicodeString& Text;
};

class StringObjectItemRow:public StackLayout {
private:
    TextBlock* tv;
    TextBlock* tv2;
    ImageView* imageView;

public:
    StringObjectItemRow(ResourceContext& context, Theme& theme) {
        preferredSize.height = PreferredSize::Height::WRAP;
        ScopedPointer<ColorView> colorView = ghnew ColorView(theme.getColorBackground());

        ScopedPointer<PaddingContainer> padding = ghnew PaddingContainer();
        {
            padding->PreferredSize.width = PreferredSize::Width::FILL;
            padding->Padding.Horizontal = 16.0f;
            padding->Padding.Vertical = 8.0f;

            ScopedPointer<HorizontalLayout> row = ghnew HorizontalLayout();
            {
                row->PreferredSize.height = PreferredSize::Height::WRAP;

                ScopedPointer<Clip> clip = ghnew Clip();
                {
                    clip->Shape = ghnew Ghurund::UI::RoundRect(context.Graphics2D, 4.0f);

                    imageView = ghnew ImageView();
                    imageView->PreferredSize = { 48, 48 };
                    clip->Child = imageView;
                }

                ScopedPointer<VerticalLayout> column = ghnew VerticalLayout();
                {
                    column->PreferredSize.height = PreferredSize::Height::WRAP;
                    column->Alignment.horizontal = Alignment::Horizontal::CENTER;

                    tv = ghnew TextBlock(theme.textViewPrimaryStyle);
                    tv->PreferredSize.width = PreferredSize::Width::WRAP;
                    tv2 = ghnew TextBlock(theme.textViewSecondaryStyle);
                    tv2->PreferredSize.width = PreferredSize::Width::WRAP;
                    TextButtonPtr tb = ghnew TextButton(ghnew TextButtonAccentLayout(theme));
                    tb->Text = "CANCEL";
                    column->Children = { tv, tb, tv2 };
                }

                TextButtonPtr tb2 = ghnew TextButton(ghnew TextButtonAccentLayout(theme));
                tb2->Text = "CANCEL2";
                row->Children = { tb2, clip, makeScoped<Space>(16.0f), column };
            }
            padding->Child = row;
            ScopedPointer<ClickResponseView> responseView = ghnew ClickResponseView(theme.ColorHighlightOnBackground);

            Children = { colorView, responseView, padding };
        }
    }

    ~StringObjectItemRow() {
        tv->release();
        tv2->release();
        imageView->release();
    }

    const Ghurund::String& getText() const {
        return tv->Text;
    }

    void setText(const Ghurund::String& text) {
        tv->Text = text;
    }

    __declspec(property(get = getText, put = setText)) const String& Text;

    const String& getSubtext() const {
        return tv2->Text;
    }

    void setSubtext(const String& text) {
        tv2->Text = text;
    }

    __declspec(property(get = getSubtext, put = setSubtext)) const String& Subtext;

    inline void setImage(BitmapImage* image) {
        imageView->Image = image;
    }

    inline BitmapImage* getImage() {
        return imageView->Image;
    }

    __declspec(property(get = getImage, put = setImage)) BitmapImage* Image;

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

class StringItemAdapter:public ItemAdapter<StringObject*, Control> {
private:
    Theme& theme;
    ResourceContext& context;

public:
    StringItemAdapter(ResourceContext& context, Theme& theme):context(context), theme(theme) {}

    virtual bool canHandleItem(StringObject* const& item, size_t position) const override {
        return item->type == StringObjectType::ITEM;
    }

    virtual Control* makeControl() const override {
        return ghnew StringObjectItemRow(context, theme);
    }

    virtual void bind(Control& control, StringObject* const& item, size_t position) const override {
        StringObjectItemRow& sor = (StringObjectItemRow&)control;
        StringObjectItem* strObj = (StringObjectItem*)item;
        sor.Text = strObj->text;
        sor.Subtext = strObj->subtext;
        sor.Image = strObj->image;
    }
};
