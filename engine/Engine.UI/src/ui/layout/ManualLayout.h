#pragma once

#include "ManualLayoutManager.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
    class ManualLayout: public ControlGroup {
    private:
        ManualLayoutManager layoutManager;
        ListChildrenProvider childrenProvider = ListChildrenProvider(*this);

    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        virtual void onMeasure(float parentWidth, float parentHeight) override {
            measuredSize = layoutManager.measure(parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            layoutManager.layout(x, y, width, height);
        }

        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Core::Type& getType() const override {
            return TYPE;
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}