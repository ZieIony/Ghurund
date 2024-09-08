#pragma once

#include "ui/adapter/ItemAdapter.h"
#include "ui/drawable/Drawable.h"
#include "ui/widget/Separator.h"

namespace Ghurund::UI {
    enum class ToolbarItemType {
        BUTTON, SEPARATOR
    };

    class ToolbarItem {
    public:
        ToolbarItemType type;

        virtual ~ToolbarItem() {}
    };

    typedef std::function<void(Control&)> ClickEventHandler;

    class ButtonToolbarItem:public ToolbarItem {
    private:
        Drawable* drawable = nullptr;
        WString text;
        ClickEventHandler clickEventHandler;

    public:
        ButtonToolbarItem(Drawable* drawable, ClickEventHandler clickHandler) {
            type = ToolbarItemType::BUTTON;
            this->drawable = drawable;
            if (drawable)
                drawable->addReference();
            clickEventHandler = clickHandler;
        }

        ButtonToolbarItem(const WString& text, ClickEventHandler clickHandler) {
            type = ToolbarItemType::BUTTON;
            this->text = text;
            clickEventHandler = clickHandler;
        }

        ButtonToolbarItem(Drawable* drawable, const WString& text, ClickEventHandler clickHandler) {
            type = ToolbarItemType::BUTTON;
            this->drawable = drawable;
            if (drawable)
                drawable->addReference();
            this->text = text;
            clickEventHandler = clickHandler;
        }

        ~ButtonToolbarItem() {
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

    class SeparatorToolbarItem:public ToolbarItem {
    public:
        SeparatorToolbarItem() {
            type = ToolbarItemType::SEPARATOR;
        }
    };

}