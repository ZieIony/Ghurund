#pragma once

#include "ControlGroup.h"
#include "ui/layout/LayoutInflater.h"
#include "ui/Gravity.h"

#include <algorithm>

namespace Ghurund::UI {
    class Stack : public ControlGroup {
    private:
        inline static const char* CLASS_NAME = GH_STRINGIFY(Stack);
        inline static const BaseConstructor& CONSTRUCTOR = NoArgsConstructor<Stack>();
        
        Gravity gravity;

    public:
        inline Gravity& getGravity() {
            return gravity;
        }

        inline void setGravity(const Gravity& gravity) {
            this->gravity = gravity;
        }

        __declspec(property(get = getGravity, put = setGravity)) Gravity& Gravity;

        virtual void onMeasure() override {
            __super::onMeasure();
            measureMaxWidth();
            measureMaxHeight();
        }

        virtual void onLayout(float x, float y, float width, float height) override;

        inline static const Ghurund::Type& TYPE = TypeBuilder<Stack>(NAMESPACE_NAME, CLASS_NAME)
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::TYPE);

        virtual const Ghurund::Type& getType() const override {
            return TYPE;
        }

        static Stack* inflate(LayoutInflater& inflater, json& json);
    };
}