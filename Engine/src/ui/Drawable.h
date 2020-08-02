#pragma once

#include "Canvas.h"

#include "DirectXMath.h"

namespace Ghurund {
    using namespace DirectX;
  
    class Drawable: public Pointer {
    private:
        XMFLOAT2 position = { 0,0 };
        XMFLOAT2 size = { 0,0 };

    public:
        inline const XMFLOAT2& getPosition() const {
            return position;
        }

        inline void setPosition(XMFLOAT2& position) {
            this->position = position;
        }

        inline void setPosition(float x, float y) {
            position.x = x;
            position.y = y;
        }

        __declspec(property(get = getPosition, put = setPosition)) XMFLOAT2& Position;

        inline const XMFLOAT2& getSize() const {
            return size;
        }

        inline void setSize(XMFLOAT2& size) {
            this->size = size;
        }

        virtual void setSize(float width, float height) {
            size.x = abs(width);
            size.y = abs(height);
        }

        __declspec(property(get = getSize, put = setSize)) XMFLOAT2& Size;

        virtual void draw(Canvas& canvas) = 0;

        virtual Drawable* clone() const = 0;
    };

    class ColorDrawable :public Drawable {
    private:
        unsigned int color;
        Paint paint;

    public:
        ColorDrawable(unsigned int color):color(color) {}

        virtual void draw(Canvas& canvas) override {
            paint.Color = color;
            canvas.fillRect(Position.x, Position.y, Size.x, Size.y, paint);
        }

        virtual Drawable* clone() const {
            return ghnew ColorDrawable(color);
        }
    };
}