#pragma once

#include "ui/drawable/Drawable.h"

namespace Ghurund::Core {
    class Image;
}

namespace Ghurund::UI {
    class BitmapDrawable:public Drawable {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = BitmapDrawable::GET_TYPE();
#pragma endregion

    private:
        Image* image;

    public:
        BitmapDrawable(Image* image);

        ~BitmapDrawable();

        virtual void draw(RenderGroup& group, const FloatSize& size, const Ghurund::UI::Color& tint) const override;

        virtual BitmapDrawable* clone() const override {
            return ghnew BitmapDrawable(image);
        }
    };
}