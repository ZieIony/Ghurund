#pragma once

#include "ControlGroup.h"
#include "ui/layout/LayoutInflater.h"
#include "ui/Gravity.h"

namespace Ghurund::UI {
    class Column :public ControlGroup {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Column);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Column>();

        Gravity gravity;
        float contentHeight = 0.0f;
        unsigned int spreadCount;

    public:
        inline Gravity& getGravity() {
            return gravity;
        }

        inline void setGravity(const Gravity& gravity) {
            this->gravity = gravity;
        }

        __declspec(property(get = getGravity, put = setGravity)) Gravity& Gravity;

        virtual void onMeasure() override;

        virtual void onLayout(float x, float y, float width, float height) override;

        inline static const Ghurund::Type& TYPE = TypeBuilder<Column>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(ControlGroup::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        inline static Column* inflate(LayoutInflater& inflater, json& json) {
            Column* column = ghnew Column();
            inflater.loadChildren(column, json);
            inflater.loadControl(column, json);
            inflater.loadGravity(column, json);
            return column;
        }
    };
}