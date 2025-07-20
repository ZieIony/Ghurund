#pragma once

#include "Constraint.h"

namespace Ghurund::UI {
	class AnimatedConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = AnimatedConstraint::GET_TYPE();
#pragma endregion

	private:
		IntrusivePointer<Constraint> from, to;

		~AnimatedConstraint() {}

	public:
		AnimatedConstraint(
			const IntrusivePointer<Constraint>& from,
			const IntrusivePointer<Constraint>& to
		):from(from), to(to) {
			dependencies.putAll({ this->from.get(), this->to.get() });
		}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {

		}

		virtual AnimatedConstraint* clone() const {
			return ghnew AnimatedConstraint(*this);
		}
	};
}