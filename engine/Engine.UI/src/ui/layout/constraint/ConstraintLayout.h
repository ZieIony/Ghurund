#pragma once

#include "ui/control/ControlGroup.h"
#include "ui/Canvas.h"
#include "ui/layout/constraint/Guide.h"

namespace Ghurund::UI {
    class ConstraintLayout:public ControlGroup {
    private:
        std::unique_ptr<IStrokeStyle> strokeStyle;
        List<Guide> guides;
        bool constraintsResolved = false;
        List<Constraint*> sorted;

        Control* findChild(const AString& name) {
            for (Control* control : Children) {
                if (control->Name && *control->Name == name)
                    return control;
            }
            return nullptr;
        }

    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        virtual void onContextChanged() override;

        virtual void onMeasure(float parentWidth, float parentHeight) override;

        virtual void onLayout(float x, float y, float width, float height) override;

        virtual void load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) override;

        virtual void onDraw(ICanvas& canvas) override;

        inline List<Guide>& getGuides() {
            return guides;
        }

        __declspec(property(get = getGuides)) List<Guide>& Guides;

        void resolveConstraints();

        virtual void resolveConstraints(List<Constraint*>& constraints) override;

        void sortConstraints(List<Constraint*>& constraints);

        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ConstraintLayout::GET_TYPE();
    };
}
