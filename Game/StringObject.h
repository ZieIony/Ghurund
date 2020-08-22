#include "ui/control/ListView.h"
#include "core/string/String.h"
#include "ui/control/TextView.h"
#include "ui/control/PaddingContainer.h"
#include "ui/control/Column.h"
#include "ui/control/Clip.h"

#include "MaterialColors.h"

using namespace Ghurund::UI;

class StringObject :public Object {
private:
    inline static const char* CLASS_NAME = GH_STRINGIFY(StringObject);
    //        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<StringObject>();

public:
    String text, subtext;

    StringObject(const String& text, const String& subtext):text(text), subtext(subtext) {}

    inline static const Ghurund::Type& TYPE = TypeBuilder<StringObject>(NAMESPACE_NAME, CLASS_NAME)
        //       .withConstructor(CONSTRUCTOR)
        .withSupertype(__super::TYPE);

    virtual const Ghurund::Type& getType() const override {
        return TYPE;
    }
};

class StringObjectHeader :public TextView {
};

class StringObjectRow :public Stack {
private:
    TextView* tv;
    TextView* tv2;
    ImageView* imageView;

public:
    StringObjectRow(::Material::Theme* theme) {
        PreferredSize.height = PreferredSize::Height::WRAP;
        ScopedPointer<Surface> surface(ghnew Surface(theme->getColorSurface()));

        ScopedPointer<PaddingContainer> padding(ghnew PaddingContainer());
        {
            padding->PreferredSize.width = PreferredSize::Width::FILL;
            padding->Padding.Horizontal = 16.0f;
            padding->Padding.Vertical = 8.0f;

            ScopedPointer<Row> row(ghnew Row());
            {
                row->PreferredSize.height = PreferredSize::Height::WRAP;

                ScopedPointer<Stack> stack(ghnew Stack());
                {
                    stack->PreferredSize.width = PreferredSize::Width::WRAP;
                    stack->PreferredSize.height = PreferredSize::Height::WRAP;

                    ScopedPointer<Border> border(ghnew Border(theme->getTextColorSecondaryOnSurface()));
                    border->CornerRadius = 2;

                    ScopedPointer<Clip> clip(ghnew Clip());
                    {
                        clip->CornerRadius = 2;

                        imageView = ghnew ImageView();
                        imageView->PreferredSize.width = PreferredSize::Width(56);
                        imageView->PreferredSize.height = PreferredSize::Height(56);
                        clip->Child = imageView;
                    }

                    stack->Children.add({ clip, border });
                }

                ScopedPointer<Space> space(ghnew Space());
                space->PreferredSize.width = PreferredSize::Width(16);

                ScopedPointer<Column> column(ghnew Column());
                {
                    column->PreferredSize.height = PreferredSize::Height::WRAP;
                    column->Gravity.horizontal = Gravity::Horizontal::RIGHT;

                    tv = ghnew TextView();
                    tv->PreferredSize.width = PreferredSize::Width::FILL;
                    tv->OnStateChanged.add(theme->getTextViewStateHandler());
                    tv->Text = "H";
                    tv2 = ghnew TextView();
                    tv2->PreferredSize.width = PreferredSize::Width::FILL;
                    tv2->OnStateChanged.add(theme->getTextViewStateHandler());
                    tv2->Text = "H";
                    ScopedPointer<TextButton> tb = ghnew TextButton();
                    tb->OnStateChanged.add(theme->getTextButtonStateHandler());
                    tb->Text = "CANCEL";
                    column->Children.add({ tv, tv2, tb });
                }

                row->Children.add({ stack, space, column });
            }
            padding->Child = row;

            Children.add({ surface, padding });
        }
    }

    ~StringObjectRow() {
        tv->release();
        tv2->release();
        imageView->release();
    }

    const String& getText() const {
        return tv->Text;
    }

    void setText(const String& text) {
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

class StringHeaderAdapter :public ItemAdapter<String*> {
public:
    virtual Control* makeControl() const override {
        return ghnew StringObjectHeader();
    }

    virtual void bind(String* const& obj, Control& control) const override {
        StringObjectHeader& sor = (StringObjectHeader&)control;
        sor.Text = *obj;
    }
};

class StringItemAdapter :public ItemAdapter<StringObject*> {
private:
    ::Material::Theme* theme;
    GdiImage* image;

public:
    StringItemAdapter(::Material::Theme* theme, GdiImage* image):theme(theme), image(image) {}

    virtual Control* makeControl() const override {
        return ghnew StringObjectRow(theme);
    }

    virtual void bind(StringObject* const& obj, Control& control) const override {
        StringObjectRow& sor = (StringObjectRow&)control;
        sor.Text = obj->text;
        sor.Subtext = obj->subtext;
        sor.Image = image;
    }
};
