#pragma once

#include "ui/control/ControlGroup.h"
#include "ui/layout/StackLayoutManager.h"

namespace Ghurund::UI {
    class StackLayout : public ControlGroup {
    private:
        StackLayoutManager layoutManager;
        ListChildrenProvider childrenProvider = ListChildrenProvider(*this);

    protected:
        static const Ghurund::Type& GET_TYPE();

    public:
        StackLayout() {
            layoutManager.setGroup(*this, childrenProvider);
        }

        inline Alignment& getAlignment() {
            return layoutManager.alignment;
        }

        inline void setAlignment(const Alignment& alignment) {
            layoutManager.alignment = alignment;
        }

        __declspec(property(get = getAlignment, put = setAlignment)) Alignment& Alignment;

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            measuredSize = layoutManager.measure(parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            layoutManager.layout(x, y, width, height);
        }

        virtual Status load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };
}