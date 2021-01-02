#pragma once

#include "core/SharedPointer.h"
#include "ui/control/ControlGroup.h"
#include "ui/layout/StackLayoutManager.h"

namespace Ghurund::UI {
    class StackLayout : public ControlGroup {
    private:
        StackLayoutManager layoutManager;
        ListChildrenProvider childrenProvider = ListChildrenProvider(*this);

        static inline const auto& CONSTRUCTOR = NoArgsConstructor<StackLayout>();
        static const Ghurund::Type& GET_TYPE() {
            static const Ghurund::Type TYPE = TypeBuilder(NAMESPACE_NAME, GH_STRINGIFY(StackLayout))
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

        virtual void onMeasure(float parentWidth, float parentHeight) override {
            measuredSize = layoutManager.measure(*this, childrenProvider, parentWidth, parentHeight);
        }

        virtual void onLayout(float x, float y, float width, float height) override {
            layoutManager.layout(*this, childrenProvider, x, y, width, height);
        }

        virtual Status load(LayoutLoader& loader, ResourceContext& context, const tinyxml2::XMLElement& xml) override;

        inline static const Ghurund::Type& TYPE = GET_TYPE();

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }
    };

    typedef SharedPointer<StackLayout> StackLayoutPtr;
}