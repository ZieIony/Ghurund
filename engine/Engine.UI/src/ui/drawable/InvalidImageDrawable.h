#pragma once

#include "ImageDrawable.h"
#include "ui/Color.h"

namespace Ghurund::UI {
    class InvalidImageDrawable:public ImageDrawable {
    private:
        Color backgroundColor = Color(1, 0, 0, 0.2f);
        Color borderColor = Color(1, 0, 0, 1.0f);

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        InvalidImageDrawable();

        virtual void onDraw(ICanvas& canvas) override;

        virtual InvalidImageDrawable* clone() const override {
            return ghnew InvalidImageDrawable();
        }
    };
}