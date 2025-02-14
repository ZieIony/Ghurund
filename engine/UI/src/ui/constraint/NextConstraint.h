#pragma once

#include "OffsetConstraint.h"
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

		inline static const Ghurund::Core::Type& TYPE = NextLeftConstraint::GET_TYPE();
#pragma endregion

	public:
		NextLeftConstraint():OffsetConstraint(false, false) {}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value + offset;
			} else {
				value = 0;
			}
			evaluated = true;
		}

		virtual NextLeftConstraint* clone() const {
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

		inline static const Ghurund::Core::Type& TYPE = NextRightConstraint::GET_TYPE();
#pragma endregion

	public:
		NextRightConstraint():OffsetConstraint(false, false) {}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value + offset;
			} else {
				value = 0;
			}
			evaluated = true;
		}

		virtual NextRightConstraint* clone() const {
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

		inline static const Ghurund::Core::Type& TYPE = NextTopConstraint::GET_TYPE();
#pragma endregion

	public:
		NextTopConstraint():OffsetConstraint(false, false) {}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value + offset;
			} else {
				value = 0;
			}
			evaluated = true;
		}

		virtual NextTopConstraint* clone() const {
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

		inline static const Ghurund::Core::Type& TYPE = NextBottomConstraint::GET_TYPE();
#pragma endregion

	public:
		NextBottomConstraint():OffsetConstraint(false, false) {}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value + offset;
			} else {
				value = 0;
			}
			evaluated = true;
		}

		virtual NextBottomConstraint* clone() const {
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

		inline static const Ghurund::Core::Type& TYPE = NextWidthConstraint::GET_TYPE();
#pragma endregion

	public:
		NextWidthConstraint():MinMaxConstraint(false, false) {}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
			} else {
				value = minMax(min, offset, max);
			}
			evaluated = true;
		}

		virtual NextWidthConstraint* clone() const {
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

		inline static const Ghurund::Core::Type& TYPE = NextHeightConstraint::GET_TYPE();
#pragma endregion

	public:
		NextHeightConstraint():MinMaxConstraint(false, false) {}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
			} else {
				value = minMax(min, offset, max);
			}
			evaluated = true;
		}

		virtual NextHeightConstraint* clone() const {
			return ghnew NextHeightConstraint(*this);
		}
	};
}