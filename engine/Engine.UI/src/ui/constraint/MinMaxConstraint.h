#pragma once

#include "RatioConstraint.h"

namespace Ghurund::UI {
	class Control;
	class ConstraintGraph;

	using namespace Ghurund::Core;

	class MinMaxConstraint:public RatioConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();
#pragma endregion

	protected:
		float min = std::numeric_limits<float>::lowest(), max = std::numeric_limits<float>::max();

		virtual bool equalsImpl(const Object& other) const override;

		MinMaxConstraint(const MinMaxConstraint& other):RatioConstraint(other), min(other.min), max(other.max) {}

	public:
		MinMaxConstraint() {}

		MinMaxConstraint(bool constant, bool skipDependencies):RatioConstraint(constant, skipDependencies) {}

		inline float getMin() const {
			return min;
		}

		inline void setMin(float min) {
			if (min > max)
				throw InvalidParamException();
			this->min = min;
			value = std::max(value, min);
		}

		__declspec(property(get = getMin, put = setMin)) float Min;

		inline float getMax() const {
			return max;
		}

		inline void setMax(float max) {
			if (max < min)
				throw InvalidParamException();
			this->max = max;
			value = std::min(value, min);
		}

		__declspec(property(get = getMax, put = setMax)) float Max;

		virtual Object* clone() const {
			return ghnew MinMaxConstraint(*this);
		}
	};
}
