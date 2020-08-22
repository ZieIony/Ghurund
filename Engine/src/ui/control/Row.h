#pragma once

#include "ControlGroup.h"
#include "ui/layout/LayoutInflater.h"
#include "ui/Gravity.h"

namespace Ghurund::UI {
    class Row :public ControlGroup {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Row);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Row>();

        Gravity gravity;
        float contentWidth = 0.0f;
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

        inline static const Ghurund::Type& TYPE = TypeBuilder<Row>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(ControlGroup::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        inline static Row* inflate(LayoutInflater& inflater, json& json) {
            Row* row = ghnew Row();
            inflater.loadChildren(row, json);
            inflater.loadControl(row, json);
            inflater.loadGravity(row, json);
            return row;
        }
    };
}