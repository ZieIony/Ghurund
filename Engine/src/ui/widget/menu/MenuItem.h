#pragma once

#include "ui/adapter/ItemAdapter.h"
#include "ui/widget/button/ImageButton.h"
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
        BitmapImage* image = nullptr;
        WString text;
        ClickEventHandler clickEventHandler;

    public:
        ButtonMenuItem(BitmapImage* image, ClickEventHandler clickHandler) {
            type = MenuItemType::BUTTON;
            this->image = image;
            if (image)
                image->addReference();
            clickEventHandler = clickHandler;
        }

        ButtonMenuItem(const WString& text, ClickEventHandler clickHandler) {
            type = MenuItemType::BUTTON;
            this->text = text;
            clickEventHandler = clickHandler;
        }

        ButtonMenuItem(BitmapImage* image, const WString& text, ClickEventHandler clickHandler) {
            type = MenuItemType::BUTTON;
            this->image = image;
            if (image)
                image->addReference();
            this->text = text;
            clickEventHandler = clickHandler;
        }

        ~ButtonMenuItem() {
            if(image)
                image->release();
            delete[] text;
        }

        inline void setImage(BitmapImage* image) {
            this->image = image;
        }

        inline BitmapImage* getImage() {
            return image;
        }

        __declspec(property(get = getImage, put = setImage)) BitmapImage* Image;

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