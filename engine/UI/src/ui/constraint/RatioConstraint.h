#pragma once

#include "OffsetConstraint.h"

namespace Ghurund::UI {
	class Control;
	class ConstraintGraph;

	using namespace Ghurund::Core;

	class RatioConstraint:public OffsetConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = RatioConstraint::GET_TYPE();
#pragma endregion

	protected:
		float ratio = 1.0f;

		virtual bool equalsImpl(const Object& other) const override;

		RatioConstraint(const RatioConstraint& other):OffsetConstraint(other), ratio(other.ratio) {}

		~RatioConstraint() = 0 {}

	public:
		RatioConstraint() {}

		RatioConstraint(bool constant, bool skipDependencies):OffsetConstraint(constant, skipDependencies) {}

		inline float getRatio() const {
			return ratio;
		}

		inline void setRatio(float ratio) {
			if (ratio <= 0.0f)
				throw InvalidParamException();
			this->ratio = ratio;
		}

		__declspec(property(get = getRatio, put = setRatio)) float Ratio;
	};
}
