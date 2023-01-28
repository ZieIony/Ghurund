#pragma once

#include "DragHelper.h"
#include "Widget.h"
#include "ui/control/ClickableControl.h"
#include "ui/control/ControlGroup.h"
#include "ui/widget/button/Button.h"

#include <algorithm>

namespace Ghurund::UI {
    class VerticalScrollBar:public Widget {
    private:
        Button* topButton;
        Button* barButton;
        ClickableControl* clickableTrack;
        ControlGroup* track;
        Button* bottomButton;

        uint32_t pressMousePos = 0;
        float pressBarPos = 0;
        DragHelper* dragHelper = nullptr;

        float scroll = 0;
        float maxScroll = 100;
        Event<Control> onScrolled = Event<Control>(*this);

        void updateBar();

        void updateScroll();

    protected:
        virtual void bind() override;

        static const Ghurund::Core::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = Constructor<VerticalScrollBar>();
            static const Ghurund::Core::Type TYPE = TypeBuilder<VerticalScrollBar>(NAMESPACE_NAME, GH_STRINGIFY(VerticalScrollBar))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return GET_TYPE();
        }

    public:
        ~VerticalScrollBar() {
            delete dragHelper;
        }

        inline float getScroll() const {
            return scroll;
        }

        inline void setScroll(float scroll) {
            this->scroll = std::max(0.0f, std::min(scroll, maxScroll));
            updateBar();
        }

        __declspec(property(get = getScroll, put = setScroll)) float Scroll;

        inline float getMaxScroll() const {
            return maxScroll;
        }

        inline void setMaxScroll(float maxScroll) {
            this->maxScroll = std::max(0.0f, maxScroll);
            Scroll = std::max(0.0f, std::min(scroll, maxScroll));
        }

        __declspec(property(get = getMaxScroll, put = setMaxScroll)) float MaxScroll;

        inline Event<Control>& getOnScrolled() {
            return onScrolled;
        }

        __declspec(property(get = getOnScrolled)) Event<Control>& OnScrolled;

        

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };

    typedef SharedPointer<VerticalScrollBar> VerticalScrollBarPtr;
}