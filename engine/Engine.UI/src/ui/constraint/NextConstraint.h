#pragma once

#include "OffsetConstraint.h"
#include "ValueConstraint.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
	class NextLeftConstraint:public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = (*dependencies.begin())->Value + offset;
		}

		virtual Object* clone() const {
			return ghnew NextLeftConstraint(*this);
		}
	};

	class NextRightConstraint:public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = (*dependencies.begin())->Value + offset;
		}

		virtual Object* clone() const {
			return ghnew NextRightConstraint(*this);
		}
	};

	class NextTopConstraint: public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = (*dependencies.begin())->Value + offset;
		}

		virtual Object* clone() const {
			return ghnew NextTopConstraint(*this);
		}
	};

	class NextBottomConstraint:public OffsetConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = (*dependencies.begin())->Value + offset;
		}

		virtual Object* clone() const {
			return ghnew NextBottomConstraint(*this);
		}
	};

	class NextWidthConstraint:public MinMaxConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
		}

		virtual Object* clone() const {
			return ghnew NextWidthConstraint(*this);
		}
	};

	class NextHeightConstraint:public MinMaxConstraint {
	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty)
				value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
		}

		virtual Object* clone() const {
			return ghnew NextHeightConstraint(*this);
		}
	};
}