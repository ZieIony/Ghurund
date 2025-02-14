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

		inline static const Ghurund::Core::Type& TYPE = PreviousLeftConstraint::GET_TYPE();
#pragma endregion

	public:
		PreviousLeftConstraint():OffsetConstraint(false, false) {}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override;

		virtual PreviousLeftConstraint* clone() const {
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

		inline static const Ghurund::Core::Type& TYPE = PreviousRightConstraint::GET_TYPE();
#pragma endregion

	public:
		PreviousRightConstraint():OffsetConstraint(false, false) {}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override;

		virtual PreviousRightConstraint* clone() const {
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

		inline static const Ghurund::Core::Type& TYPE = PreviousTopConstraint::GET_TYPE();
#pragma endregion

	public:
		PreviousTopConstraint():OffsetConstraint(false, false) {}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override;

		virtual PreviousTopConstraint* clone() const {
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

		inline static const Ghurund::Core::Type& TYPE = PreviousBottomConstraint::GET_TYPE();
#pragma endregion

	public:
		PreviousBottomConstraint():OffsetConstraint(false, false) {}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override;

		virtual PreviousBottomConstraint* clone() const {
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

		inline static const Ghurund::Core::Type& TYPE = PreviousWidthConstraint::GET_TYPE();
#pragma endregion

	public:
		PreviousWidthConstraint():MinMaxConstraint(false, false) {}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override;

		virtual PreviousWidthConstraint* clone() const {
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

		inline static const Ghurund::Core::Type& TYPE = PreviousHeightConstraint::GET_TYPE();
#pragma endregion

	public:
		PreviousHeightConstraint():MinMaxConstraint(false, false) {}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override;

		virtual PreviousHeightConstraint* clone() const {
			return ghnew PreviousHeightConstraint(*this);
		}
	};
}