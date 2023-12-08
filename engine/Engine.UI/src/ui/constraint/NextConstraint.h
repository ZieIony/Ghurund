#pragma once

#include "OffsetConstraint.h"
#include "ValueConstraint.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
	class NextLeftConstraint:public OffsetConstraint {
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
			return ghnew NextLeftConstraint(*this);
		}
	};

	class NextRightConstraint:public OffsetConstraint {
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
			return ghnew NextRightConstraint(*this);
		}
	};

	class NextTopConstraint: public OffsetConstraint {
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
			return ghnew NextTopConstraint(*this);
		}
	};

	class NextBottomConstraint:public OffsetConstraint {
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
			return ghnew NextBottomConstraint(*this);
		}
	};

	class NextWidthConstraint:public MinMaxConstraint {
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
			return ghnew NextWidthConstraint(*this);
		}
	};

	class NextHeightConstraint:public MinMaxConstraint {
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
			return ghnew NextHeightConstraint(*this);
		}
	};
}