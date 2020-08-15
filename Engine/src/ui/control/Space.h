#pragma once

#include "Control.h"
#include "ui/layout/LayoutInflater.h"

namespace Ghurund::UI {
    class Space :public Control {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Space);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Space>();

    public:
        Space() {
            preferredSize.width = PreferredSize::Width(8.0f);
            preferredSize.height = PreferredSize::Height(8.0f);
        }

        virtual void draw(Canvas& canvas) {}

        inline static const Ghurund::Type& TYPE = TypeBuilder<Space>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        inline static Space* inflate(LayoutInflater& inflater, json& json) {
            Space* space = ghnew Space();
            inflater.loadControl(space, json);
            return space;
        }
    };
}