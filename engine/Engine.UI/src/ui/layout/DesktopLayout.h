#pragma once

#include "ManualLayoutManager.h"

#include "ui/Alignment.h"
#include "ui/control/ControlGroup.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
    class DesktopLayout:public ControlGroup {
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

        

        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
    };
}