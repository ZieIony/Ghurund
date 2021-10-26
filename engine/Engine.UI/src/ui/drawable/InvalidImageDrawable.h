#pragma once

#include "ImageDrawable.h"
#include "ui/Color.h"

namespace Ghurund::UI {
    class InvalidImageDrawable:public ImageDrawable {
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

    private:
        Color backgroundColor = Color(1, 0, 0, 0.2f);
        Color borderColor = Color(1, 0, 0, 1.0f);

    public:
        InvalidImageDrawable();

        virtual void onDraw(ICanvas& canvas) override;

        virtual InvalidImageDrawable* clone() const override {
            return ghnew InvalidImageDrawable();
        }
    };
}