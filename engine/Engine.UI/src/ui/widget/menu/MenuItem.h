#pragma once

#include "ui/adapter/ItemAdapter.h"
#include "ui/drawable/Drawable.h"
#include "ui/widget/Separator.h"

namespace Ghurund::UI {
    enum class MenuItemType {
        BUTTON, SEPARATOR
    };

    class MenuItem {
    public:
        MenuItemType type;

        virtual ~MenuItem() {}
    };

    typedef std::function<void(Control&)> ClickEventHandler;

    class ButtonMenuItem:public MenuItem {
    private:
        Drawable* drawable = nullptr;
        WString text;
        ClickEventHandler clickEventHandler;

    public:
        ButtonMenuItem(Drawable* drawable, ClickEventHandler clickHandler) {
            type = MenuItemType::BUTTON;
            this->drawable = drawable;
            if (drawable)
                drawable->addReference();
            clickEventHandler = clickHandler;
        }

        ButtonMenuItem(const WString& text, ClickEventHandler clickHandler) {
            type = MenuItemType::BUTTON;
            this->text = text;
            clickEventHandler = clickHandler;
        }

        ButtonMenuItem(Drawable* drawable, const WString& text, ClickEventHandler clickHandler) {
            type = MenuItemType::BUTTON;
            this->drawable = drawable;
            if (drawable)
                drawable->addReference();
            this->text = text;
            clickEventHandler = clickHandler;
        }

        ~ButtonMenuItem() {
            if(drawable)
                drawable->release();
        }

        inline void setImage(Drawable* drawable) {
            this->drawable = drawable;
        }

        inline Drawable* getImage() {
            return drawable;
        }

        __declspec(property(get = getImage, put = setImage)) Drawable* Image;

        inline void setText(const WString& text) {
            this->text = text;
        }

        inline const WString& getText() {
            return text;
        }

        __declspec(property(get = getText, put = setText)) const WString Text;

        inline ClickEventHandler getClickEventHandler() {
            return clickEventHandler;
        }

        inline void setClickEventHandler(ClickEventHandler clickEventHandler) {
            this->clickEventHandler = clickEventHandler;
        }

        __declspec(property(get = getClickEventHandler, put = setClickEventHandler)) ClickEventHandler ClickEventHandler;
    };

    class SeparatorMenuItem:public MenuItem {
    public:
        SeparatorMenuItem() {
            type = MenuItemType::SEPARATOR;
        }
    };

}