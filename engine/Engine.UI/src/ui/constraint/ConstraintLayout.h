#pragma once

#include "Guide.h"
#include "ui/control/ControlGroup.h"
#include "ui/Canvas.h"

namespace Ghurund::UI {
    class ConstraintLayout:public ControlGroup {
    private:
        std::unique_ptr<IStrokeStyle> strokeStyle;
        List<Guide> guides;

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

        virtual void onLayout(float x, float y, float width, float height) override;

        virtual void load(LayoutLoader& loader, ResourceManager& resourceManager, const tinyxml2::XMLElement& xml) override;

        virtual void onDraw(ICanvas& canvas) override;

        inline List<Guide>& getGuides() {
            return guides;
        }

        __declspec(property(get = getGuides)) List<Guide>& Guides;

        virtual void resolveConstraints(ConstraintGraph& graph) override;

        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ConstraintLayout::GET_TYPE();
    };
}
