#pragma once

#include "ui/Alignment.h"
#include "ui/control/ControlGroup.h"
#include "ui/layout/LinearLayoutManager.h"

namespace Ghurund::UI {
    class LinearLayout:public ControlGroup {
    private:
        LinearLayoutManager layoutManager;
        ListChildrenProvider childrenProvider = ListChildrenProvider(*this);

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        LinearLayout() {
            layoutManager.setGroup(*this, childrenProvider);
        }

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

        virtual bool focusUp() override;

        virtual bool focusDown() override;

        virtual bool focusLeft() override;

        virtual bool focusRight() override;

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            measuredSize = layoutManager.measure(parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            layoutManager.layout(x, y, width, height);
        }

        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }
    };

    class HorizontalLayout:public LinearLayout {};

    class VerticalLayout:public LinearLayout {
    public:
        VerticalLayout() {
            Orientation = Orientation::VERTICAL;
        }
    };
}