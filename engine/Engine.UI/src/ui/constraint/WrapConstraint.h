#pragma once

#include "MinMaxConstraint.h"
#include "core/SharedPointer.h"

namespace Ghurund::UI {

    class WrapWidthConstraint:public MinMaxConstraint {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = WrapWidthConstraint::GET_TYPE();
#pragma endregion

    protected:
        WrapWidthConstraint(const WrapWidthConstraint& other):MinMaxConstraint(other) {}

    public:
        WrapWidthConstraint():MinMaxConstraint(false, true) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;

        virtual WrapWidthConstraint* clone() const {
            return ghnew WrapWidthConstraint(*this);
        }
    };

    class WrapHeightConstraint:public MinMaxConstraint {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = WrapHeightConstraint::GET_TYPE();
#pragma endregion

    protected:
        WrapHeightConstraint(const WrapHeightConstraint& other):MinMaxConstraint(other) {}

    public:
        WrapHeightConstraint():MinMaxConstraint(false, true) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;

        virtual WrapHeightConstraint* clone() const {
            return ghnew WrapHeightConstraint(*this);
        }
    };
}