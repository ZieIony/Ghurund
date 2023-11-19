#pragma once

#include "OffsetConstraint.h"
#include "ValueConstraint.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
	class PreviousLeftConstraint:public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = (*dependencies.begin())->Value + offset;
		}

		virtual Object* clone() const {
			return ghnew PreviousLeftConstraint(*this);
		}
	};

	class PreviousRightConstraint:public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = (*dependencies.begin())->Value + offset;
		}

		virtual Object* clone() const {
			return ghnew PreviousRightConstraint(*this);
		}
	};

	class PreviousTopConstraint: public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = (*dependencies.begin())->Value + offset;
		}

		virtual Object* clone() const {
			return ghnew PreviousTopConstraint(*this);
		}
	};

	class PreviousBottomConstraint:public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = (*dependencies.begin())->Value + offset;
		}

		virtual Object* clone() const {
			return ghnew PreviousBottomConstraint(*this);
		}
	};

	class PreviousWidthConstraint:public MinMaxConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
		}

		virtual Object* clone() const {
			return ghnew PreviousWidthConstraint(*this);
		}
	};

	class PreviousHeightConstraint:public MinMaxConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
		}

		virtual Object* clone() const {
			return ghnew PreviousHeightConstraint(*this);
		}
	};
}