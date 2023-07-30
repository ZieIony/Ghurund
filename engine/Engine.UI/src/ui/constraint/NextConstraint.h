#pragma once

#include "Constraint.h"
#include "ValueConstraint.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
	class NextLeftConstraint:public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = (*dependencies.begin())->Value + offset;
		}
	};

	class NextRightConstraint:public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = (*dependencies.begin())->Value + offset;
		}
	};

	class NextTopConstraint: public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = (*dependencies.begin())->Value + offset;
		}
	};

	class NextBottomConstraint:public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = (*dependencies.begin())->Value + offset;
		}
	};

	class NextWidthConstraint:public MinMaxConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
		}
	};

	class NextHeightConstraint:public MinMaxConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
		}
	};
}