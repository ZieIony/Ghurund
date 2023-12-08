#pragma once

#include "OffsetConstraint.h"
#include "ValueConstraint.h"
#include "core/math/MathUtils.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
	class ParentLeftConstraint:public OffsetConstraint {
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
		virtual void resolve(Control& control, ConstraintGraph& graph) override {
			evaluated = false;
		}

		virtual void evaluate() override {
			value = offset;
			evaluated = true;
		}
	};

	class ParentRightConstraint:public OffsetConstraint {
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
			return ghnew ParentRightConstraint(*this);
		}
	};

	class ParentTopConstraint:public OffsetConstraint {
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
		virtual void resolve(Control& control, ConstraintGraph& graph) override {
			evaluated = false;
		}

		virtual void evaluate() override {
			value = offset;
			evaluated = true;
		}
	};

	class ParentBottomConstraint:public OffsetConstraint {
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
			return ghnew ParentBottomConstraint(*this);
		}
	};

	class ParentWidthConstraint:public MinMaxConstraint {
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
			return ghnew ParentWidthConstraint(*this);
		}
	};

	class ParentHeightConstraint:public MinMaxConstraint {
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
			return ghnew ParentHeightConstraint(*this);
		}
	};
}