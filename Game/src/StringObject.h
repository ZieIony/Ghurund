#pragma once

#include "MaterialColors.h"

#include "core/ScopedPointer.h"
#include "core/string/String.h"
#include "ui/adapter/AdapterView.h"
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

    StringObjectItem(const Ghurund::String& text, const Ghurund::String& subtext):text(text), subtext(subtext) {
        type = StringObjectType::ITEM;
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
        Children = {
            makeColorView(theme.getColorBackground()),
            padding
        };
    }

    Ghurund::String& getText() {
        return tv->Text;
    }

    void setText(const Ghurund::String& text) {
        tv->Text = text;
    }

    __declspec(property(get = getText, put = setText)) const String& Text;
};

class StringObjectItemRow:public StackLayout {
private:
    TextBlock* tv;
    TextBlock* tv2;
    ImageView* imageView;

public:
    StringObjectItemRow(Theme& theme) {
        preferredSize.height = PreferredSize::Height::WRAP;
        ColorViewPtr colorView = ghnew ColorView(theme.getColorBackground());

        PaddingContainerPtr padding = ghnew PaddingContainer();
        {
            padding->PreferredSize.width = PreferredSize::Width::FILL;
            padding->Padding.Horizontal = 16.0f;
            padding->Padding.Vertical = 8.0f;

            HorizontalLayoutPtr row = ghnew HorizontalLayout();
            {
                row->PreferredSize.height = PreferredSize::Height::WRAP;

                StackLayoutPtr stack = ghnew StackLayout();
                {
                    stack->PreferredSize = { PreferredSize::Width::WRAP, PreferredSize::Height::WRAP };

                    BorderPtr border = ghnew Border(theme.getColorControl());
                    border->CornerRadius = 2;

                    ClipPtr clip = ghnew Clip();
                    {
                        clip->CornerRadius = 2;

                        imageView = ghnew ImageView();
                        imageView->PreferredSize = { 56, 56 };
                        clip->Child = imageView;
                    }

                    stack->Children = { clip, border };
                }

                SpacePtr space = ghnew Space();
                space->PreferredSize.width = 16;

                VerticalLayoutPtr column = ghnew VerticalLayout();
                {
                    column->PreferredSize.height = PreferredSize::Height::WRAP;
                    column->Alignment.horizontal = Alignment::Horizontal::RIGHT;

                    tv = ghnew TextBlock(theme.textViewPrimaryStyle);
                    tv->PreferredSize.width = PreferredSize::Width::FILL;
                    tv2 = ghnew TextBlock(theme.textViewSecondaryStyle);
                    tv2->PreferredSize.width = PreferredSize::Width::FILL;
                    TextButtonPtr tb = ghnew TextButton(ghnew TextButtonAccentLayout(theme));
                    tb->Text = "CANCEL";
                    column->Children = { tv, tv2, tb };
                }

                row->Children = { stack, space, column };
            }
            padding->Child = row;
            ScopedPointer<ClickResponseView> responseView = ghnew ClickResponseView();
            responseView->PreferredSize = { PreferredSize::Width::FILL, PreferredSize::Height::WRAP };
            responseView->Child = padding;

            Children = { colorView, responseView };
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

class StringHeaderAdapter:public ItemAdapter<StringObject*, Control>{
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
    Gdiplus::Image* image = nullptr;

public:
    StringItemAdapter(Theme& theme, Gdiplus::Image* image):theme(theme) {
            this->image = image;
    }

    ~StringItemAdapter() {
        if (image)
            delete image;
    }

    virtual bool canHandleItem(StringObject* const& item, size_t position) const override {
        return item->type == StringObjectType::ITEM;
    }

    virtual Control* makeControl() const override {
        return ghnew StringObjectItemRow(theme);
    }

    virtual void bind(Control& control, StringObject* const& item, size_t position) const override {
        StringObjectItemRow& sor = (StringObjectItemRow&)control;
        StringObjectItem* strObj = (StringObjectItem*)item;
        sor.Text = strObj->text;
        sor.Subtext = strObj->subtext;
        sor.Image = ghnew BitmapImage(image);
    }
};
