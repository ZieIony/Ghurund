#pragma once

#include "ui/constraint/OffsetConstraint.h"
#include "ui/constraint/ValueConstraint.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
	class SpringWidthConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = SpringWidthConstraint::GET_TYPE();
#pragma endregion

	private:
		float weight = 1.0f, totalWeight = 0.0f;
		SharedPointer<Constraint> parentWidth;

	public:
		inline float getWeight() const {
			return weight;
		}

		inline void setWeight(float weight) {
			this->weight = weight;
		}

		__declspec(property(get = getWeight, put = setWeight)) float Weight;

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			float width = parentWidth->Value;
			for (Constraint* c : dependencies)
				width -= c->Value;
			value = width * weight / totalWeight;
			evaluated = true;
		}

		virtual SpringWidthConstraint* clone() const {
			return ghnew SpringWidthConstraint(*this);
		}
	};

	class SpringHeightConstraint:public MinMaxConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = SpringHeightConstraint::GET_TYPE();
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

		virtual SpringHeightConstraint* clone() const {
			return ghnew SpringHeightConstraint(*this);
		}
	};
}