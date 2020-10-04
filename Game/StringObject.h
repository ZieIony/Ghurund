#include "ui/control/AdapterView.h"
#include "core/string/String.h"
#include "ui/control/TextView.h"
#include "ui/control/PaddingContainer.h"
#include "ui/control/LinearLayout.h"
#include "ui/control/Clip.h"
#include "ui/control/ColorView.h"
#include "core/ScopedPointer.h"

#include "MaterialColors.h"

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
    ScopedPointer<TextView> tv;
    ScopedPointer<PaddingContainer> padding;
    ScopedPointer<ColorView> backgroundView;

public:
    StringObjectHeaderRow(Theme& theme) {
        preferredSize.height = PreferredSize::Height::WRAP;
        backgroundView = ghnew ColorView(theme.getColorBackground());

        padding = ghnew PaddingContainer();
        {
            padding->PreferredSize.width = PreferredSize::Width::FILL;
            padding->Padding.Horizontal = 16.0f;
            padding->Padding.Vertical = 4.0f;

            tv = ghnew TextView(theme.textViewHeaderStyle);
            tv->PreferredSize.width = PreferredSize::Width::FILL;
            padding->Child = tv;

        }
        Children = { backgroundView, padding };
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
    TextView* tv;
    TextView* tv2;
    ImageView* imageView;

public:
    StringObjectItemRow(Theme& theme) {
        preferredSize.height = PreferredSize::Height::WRAP;
        ScopedPointer<ColorView> colorView(ghnew ColorView(theme.getColorBackground()));

        ScopedPointer<PaddingContainer> padding(ghnew PaddingContainer());
        {
            padding->PreferredSize.width = PreferredSize::Width::FILL;
            padding->Padding.Horizontal = 16.0f;
            padding->Padding.Vertical = 8.0f;

            HorizontalLayoutPtr row = ghnew HorizontalLayout();
            {
                row->PreferredSize.height = PreferredSize::Height::WRAP;

                StackLayoutPtr stack = ghnew StackLayout();
                {
                    stack->PreferredSize.width = PreferredSize::Width::WRAP;
                    stack->PreferredSize.height = PreferredSize::Height::WRAP;

                    BorderPtr border = ghnew Border(theme.getColorControl());
                    border->CornerRadius = 2;

                    ScopedPointer<Clip> clip(ghnew Clip());
                    {
                        clip->CornerRadius = 2;

                        imageView = ghnew ImageView();
                        imageView->PreferredSize.width = PreferredSize::Width(56);
                        imageView->PreferredSize.height = PreferredSize::Height(56);
                        clip->Child = imageView;
                    }

                    stack->Children = { clip, border };
                }

                ScopedPointer<Space> space(ghnew Space());
                space->PreferredSize.width = PreferredSize::Width(16);

                VerticalLayoutPtr column = ghnew VerticalLayout();
                {
                    column->PreferredSize.height = PreferredSize::Height::WRAP;
                    column->Gravity.horizontal = Gravity::Horizontal::RIGHT;

                    tv = ghnew TextView(theme.textViewPrimaryStyle);
                    tv->PreferredSize.width = PreferredSize::Width::FILL;
                    tv2 = ghnew TextView(theme.textViewSecondaryStyle);
                    tv2->PreferredSize.width = PreferredSize::Width::FILL;
                    TextButtonPtr tb = ghnew TextButton(ghnew TextButtonAccentLayout(theme));
                    tb->Text = "CANCEL";
                    column->Children = { tv, tv2, tb };
                }

                row->Children = { stack, space, column };
            }
            padding->Child = row;

            Children = { colorView, padding };
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

    inline void setImage(GdiImage* image) {
        imageView->Image = image;
    }

    inline GdiImage* getImage() {
        return imageView->Image;
    }

    __declspec(property(get = getImage, put = setImage)) GdiImage* Image;

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
    GdiImage* image = nullptr;

public:
    StringItemAdapter(Theme& theme, GdiImage* image):theme(theme) {
        if (image) {
            image->addReference();
            this->image = image;
        }
    }

    ~StringItemAdapter() {
        if (image)
            image->release();
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
        sor.Image = image;
    }
};