#pragma once

#include "MinMaxConstraint.h"

namespace Ghurund::UI {

    class ContentWidthConstraint:public MinMaxConstraint {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ContentWidthConstraint::GET_TYPE();
#pragma endregion

    public:
        ContentWidthConstraint():MinMaxConstraint(false, false) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;

        virtual ContentWidthConstraint* clone() const {
            return ghnew ContentWidthConstraint(*this);
        }
    };

    class ContentHeightConstraint:public MinMaxConstraint {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = ContentHeightConstraint::GET_TYPE();
#pragma endregion

    public:
        ContentHeightConstraint():MinMaxConstraint(false, false) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override;

        virtual void evaluate() override;

        virtual ContentHeightConstraint* clone() const {
            return ghnew ContentHeightConstraint(*this);
        }
    };
}