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
        static inline const auto& CONSTRUCTOR = NoArgsConstructor<LinearLayout>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(LinearLayout))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

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

        virtual bool focusUp() override;

        virtual bool focusDown() override;

        virtual bool focusLeft() override;

        virtual bool focusRight() override;

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            measuredSize = layoutManager.measure(*this, childrenProvider, parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            layoutManager.layout(*this, childrenProvider, x, y, width, height);
        }

        virtual Status load(LayoutLoader& loader, ResourceContext& context, const tinyxml2::XMLElement& xml) override {
            Status result = __super::load(loader, context, xml);
            if (result != Status::OK)
                return result;
            auto orientationAttr = xml.FindAttribute("orientation");
            if (orientationAttr)
                Orientation = strcmp(orientationAttr->Value(), "horizontal") == 0 ? Orientation::HORIZONTAL : Orientation::VERTICAL;
            return Status::OK;
        }

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
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