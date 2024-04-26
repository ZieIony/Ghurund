#pragma once

#include "ui/constraint/OffsetConstraint.h"
#include "ui/constraint/ValueConstraint.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
	class PreviousSpringLeftConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = PreviousSpringLeftConstraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value;
			} else {
				value = 0;
			}
			evaluated = true;
		}

		virtual PreviousSpringLeftConstraint* clone() const {
			return ghnew PreviousSpringLeftConstraint(*this);
		}
	};

	class PreviousSpringRightConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = PreviousSpringRightConstraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value;
			} else {
				value = 0;
			}
			evaluated = true;
		}

		virtual PreviousSpringRightConstraint* clone() const {
			return ghnew PreviousSpringRightConstraint(*this);
		}
	};

	class PreviousSpringTopConstraint: public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = PreviousSpringTopConstraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value;
			} else {
				value = 0;
			}
			evaluated = true;
		}

		virtual PreviousSpringTopConstraint* clone() const {
			return ghnew PreviousSpringTopConstraint(*this);
		}
	};

	class PreviousSpringBottomConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = PreviousSpringBottomConstraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value;
			} else {
				value = 0;
			}
			evaluated = true;
		}

		virtual PreviousSpringBottomConstraint* clone() const {
			return ghnew PreviousSpringBottomConstraint(*this);
		}
	};
}