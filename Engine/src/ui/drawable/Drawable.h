#pragma once

#include "ui/control/Control.h"

#include <DirectXMath.h>

namespace Ghurund::UI {
    using namespace DirectX;

    class Drawable:public Pointer {
    protected:
        FloatSize size = { 0, 0 };
        PreferredSize preferredSize;
        XMFLOAT2 position = { 0,0 };

        Control* owner = nullptr;

        ~Drawable() {
            if (owner)
                owner->release();
        }

    public:
        inline const XMFLOAT2& getPosition() const {
            return position;
        }

        inline void setPosition(const XMFLOAT2& position) {
            this->position = position;
        }

        inline void setPosition(float x, float y) {
            position.x = x;
            position.y = y;
        }

        __declspec(property(get = getPosition, put = setPosition)) const XMFLOAT2& Position;

        inline FloatSize& getSize() {
            return size;
        }

        inline void setSize(const FloatSize& size) {
            this->size = size;
        }

        inline void setSize(float width, float height) {
            size.width = width;
            size.height = height;
        }

        __declspec(property(get = getSize, put = setSize)) FloatSize& Size;

        inline const PreferredSize& getPreferredSize() const {
            return preferredSize;
        }

        __declspec(property(get = getPreferredSize)) const PreferredSize& PreferredSize;

        inline Control* getOwner() {
            return owner;
        }

        inline void setOwner(Control* owner) {
            setPointer(this->owner, owner);
        }

        __declspec(property(get = getOwner, put = setOwner)) Control* Owner;

        virtual void update(const Timer& timer) {}

        virtual void onDraw(Canvas& canvas) = 0;

        void draw(Canvas& canvas) {
            onDraw(canvas);
        }
    };

    class ImageDrawable:public Drawable {
    private:
        uint32_t tint = 0;

    public:
        inline void setTint(const uint32_t color) {
            this->tint = color;
        }

        inline uint32_t getTint() const {
            return tint;
        }

        __declspec(property(get = getTint, put = setTint)) uint32_t Tint;
    };
}