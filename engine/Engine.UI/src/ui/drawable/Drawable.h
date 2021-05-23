#pragma once

#include "ui/control/Control.h"

namespace Ghurund::UI {
    class Drawable:public Pointer {
    protected:
        static const Ghurund::Type& GET_TYPE() {

            static auto PROPERTY_SIZE = Ghurund::TypedProperty<Drawable, FloatSize&>("FloatSize&", "Size", (FloatSize & (Drawable::*)()) & getSize, (void(Drawable::*)(const FloatSize&)) & setSize);
            static auto PROPERTY_PREFERREDSIZE = Ghurund::TypedProperty<Drawable, const Ghurund::UI::PreferredSize&>("const PreferredSize&", "PreferredSize", (Ghurund::UI::PreferredSize & (Drawable::*)()) & getPreferredSize);
            static auto PROPERTY_OWNER = Ghurund::TypedProperty<Drawable, Control*>("Control*", "Owner", (Control * (Drawable::*)()) & getOwner, (void(Drawable::*)(Control*)) & setOwner);

            static const Ghurund::Type TYPE = Ghurund::TypeBuilder("Ghurund::UI", "Drawable")
                .withProperty(PROPERTY_SIZE)
                .withProperty(PROPERTY_PREFERREDSIZE)
                .withProperty(PROPERTY_OWNER)
                .withModifier(TypeModifier::ABSTRACT)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {

            return TYPE;
        }

    protected:
        FloatSize size = { 0, 0 };
        PreferredSize preferredSize;

        Control* owner = nullptr;

    public:
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
            this->owner = owner;
        }

        __declspec(property(get = getOwner, put = setOwner)) Control* Owner;

        virtual void update(const uint64_t time) {}

        virtual void onDraw(Canvas& canvas) = 0;

        void draw(Canvas& canvas) {
            onDraw(canvas);
        }
    };
}