#pragma once

#include "MinMaxConstraint.h"

namespace Ghurund::UI {

	class FlowWidthConstraint:public MinMaxConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

		~FlowWidthConstraint() {}

	public:
		FlowWidthConstraint():MinMaxConstraint(false, true) {}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override;

		virtual Object* clone() const {
			return ghnew FlowWidthConstraint(*this);
		}
	};

	class FlowHeightConstraint:public MinMaxConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

		~FlowHeightConstraint() {}

	public:
		FlowHeightConstraint():MinMaxConstraint(false, true) {}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override;

		virtual Object* clone() const {
			return ghnew FlowHeightConstraint(*this);
		}
	};
}