#pragma once

#include "ui/Alignment.h"
#include "ui/control/ControlGroup.h"
#include "ui/layout/LinearLayoutManager.h"

namespace Ghurund::UI {
    class LinearLayout:public ControlGroup {
    private:
        LinearLayoutManager layoutManager;

        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(LinearLayout))
                .withConstructor(NoArgsConstructor<LinearLayout>())
                .withSupertype(__super::TYPE);

            return TYPE;
        }

    public:
        inline Alignment& getAlignment() {
            return layoutManager.alignment;
        }

        inline void setAlignment(const Alignment& alignment) {
            layoutManager.alignment = alignment;
        }

        __declspec(property(get = getAlignment, put = setAlignment)) Alignment& Alignment;

        inline Orientation getOrientation() const {
            return layoutManager.orientation;
        }

        inline void setOrientation(Orientation orientation) {
            layoutManager.orientation = orientation;
        }

        __declspec(property(get = getOrientation, put = setOrientation)) Orientation Orientation;

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            measuredSize = layoutManager.measure(*this, parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            layoutManager.layout(*this, x, y, width, height);
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef ScopedPointer<LinearLayout> LinearLayoutPtr;

    class HorizontalLayout:public LinearLayout {};

    typedef ScopedPointer<HorizontalLayout> HorizontalLayoutPtr;

    inline HorizontalLayoutPtr makeHorizontalLayout(const std::initializer_list<Control*>& children) {
        auto layout = HorizontalLayoutPtr(ghnew HorizontalLayout());
        layout->Children = children;
        return layout;
    }

    class VerticalLayout:public LinearLayout {
    public:
        VerticalLayout() {
            Orientation = Orientation::VERTICAL;
        }
    };
 
    typedef ScopedPointer<VerticalLayout> VerticalLayoutPtr;

    inline VerticalLayoutPtr makeVerticalLayout(const std::initializer_list<Control*>& children) {
        auto layout = VerticalLayoutPtr(ghnew VerticalLayout());
        layout->Children = children;
        return layout;
    }
}