#pragma once

#include "ui/control/Control.h"
#include "ui/gdi/Gdi.h"

#include <DirectXMath.h>

namespace Ghurund::UI {
    using namespace DirectX;

    class Drawable:public Pointer {
    private:
        bool transformationInvalid = true;

        inline void rebuildTransformation() {
            transformation->Reset();
            transformation->Translate(position.x, position.y);
            transformationInvalid = false;
        }

    protected:
        FloatSize size = { 0, 0 };
        PreferredSize preferredSize;
        XMFLOAT2 position = { 0,0 };
        Gdiplus::Matrix* transformation;

        Control* owner = nullptr;

        ~Drawable() {
            delete transformation;
            if (owner)
                owner->release();
        }

    public:
        Drawable() {
            transformation = new Gdiplus::Matrix();
        }

        inline const XMFLOAT2& getPosition() const {
            return position;
        }

        inline void setPosition(const XMFLOAT2& position) {
            this->position = position;
            transformationInvalid = true;
        }

        inline void setPosition(float x, float y) {
            position.x = x;
            position.y = y;
            transformationInvalid = true;
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
            if (transformationInvalid)
                rebuildTransformation();
            canvas.save();
            canvas.transform(*transformation);

            onDraw(canvas);

            canvas.restore();
        }
    };
}