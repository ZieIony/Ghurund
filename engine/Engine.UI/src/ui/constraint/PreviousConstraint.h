#pragma once

#include "Constraint.h"
#include "ValueConstraint.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
	class PreviousLeftConstraint:public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = (*dependencies.begin())->Value + offset;
		}
	};

	class PreviousRightConstraint:public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = (*dependencies.begin())->Value + offset;
		}
	};

	class PreviousTopConstraint: public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = (*dependencies.begin())->Value + offset;
		}
	};

	class PreviousBottomConstraint:public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = (*dependencies.begin())->Value + offset;
		}
	};

	class PreviousWidthConstraint:public MinMaxConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
		}
	};

	class PreviousHeightConstraint:public MinMaxConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
		}
	};
}