#pragma once

#include "OffsetConstraint.h"
#include "ValueConstraint.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
	class PreviousLeftConstraint:public OffsetConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value + offset;
			} else {
				value = offset;
			}
			evaluated = true;
		}

		virtual Object* clone() const {
			return ghnew PreviousLeftConstraint(*this);
		}
	};

	class PreviousRightConstraint:public OffsetConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value + offset;
			} else {
				value = offset;
			}
			evaluated = true;
		}

		virtual Object* clone() const {
			return ghnew PreviousRightConstraint(*this);
		}
	};

	class PreviousTopConstraint: public OffsetConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value + offset;
			} else {
				value = offset;
			}
			evaluated = true;
		}

		virtual Object* clone() const {
			return ghnew PreviousTopConstraint(*this);
		}
	};

	class PreviousBottomConstraint:public OffsetConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value + offset;
			} else {
				value = offset;
			}
			evaluated = true;
		}

		virtual Object* clone() const {
			return ghnew PreviousBottomConstraint(*this);
		}
	};

	class PreviousWidthConstraint:public MinMaxConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
			} else {
				value = minMax(min, offset, max);
			}
			evaluated = true;
		}

		virtual Object* clone() const {
			return ghnew PreviousWidthConstraint(*this);
		}
	};

	class PreviousHeightConstraint:public MinMaxConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
			} else {
				value = minMax(min, offset, max);
			}
			evaluated = true;
		}

		virtual Object* clone() const {
			return ghnew PreviousHeightConstraint(*this);
		}
	};
}