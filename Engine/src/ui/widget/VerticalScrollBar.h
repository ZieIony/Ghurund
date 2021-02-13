#pragma once

#include "DragHelper.h"
#include "VerticalScrollBarLayout.h"
#include "Widget.h"

#include <algorithm>

namespace Ghurund::UI {
    class VerticalScrollBar:public Widget<VerticalScrollBarLayout> {
    private:
        uint32_t pressMousePos = 0;
        float pressBarPos = 0;
        DragHelper* dragHelper = nullptr;

        float scroll = 0;
        float maxScroll = 100;
        Event<Control> onScrolled = Event<Control>(*this);

        void updateBar();

        void updateScroll();

    protected:
        virtual void onLayoutChanged() override;

        static const Ghurund::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = NoArgsConstructor<VerticalScrollBar>();
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(VerticalScrollBar))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

    public:
        VerticalScrollBar(VerticalScrollBarLayout* layout = nullptr) {
            setPreferredSize(PreferredSize::Width::WRAP, PreferredSize::Height::FILL);
            Layout = layout;
        };

        VerticalScrollBar(LayoutLoader& loader):VerticalScrollBar(ghnew VerticalScrollBarLayout(loader)) {}

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

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef SharedPointer<VerticalScrollBar> VerticalScrollBarPtr;
}