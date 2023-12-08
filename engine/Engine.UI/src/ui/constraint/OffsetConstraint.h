#pragma once

#include "Constraint.h"

namespace Ghurund::UI {
	class Control;
	class ConstraintGraph;

	using namespace Ghurund::Core;

	class OffsetConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = OffsetConstraint::GET_TYPE();
#pragma endregion

	protected:
		float offset = 0.0f;

		virtual bool equalsImpl(const Object& other) const override;

		OffsetConstraint(const OffsetConstraint& other):Constraint(other), offset(other.offset) {}

		~OffsetConstraint() = 0 {}

	public:
		OffsetConstraint() {}

		OffsetConstraint(bool constant, bool skipDependencies):Constraint(constant, skipDependencies) {}

		inline float getOffset() const {
			return offset;
		}

		inline void setOffset(float offset) {
			this->offset = offset;
		}

		__declspec(property(get = getOffset, put = setOffset)) float Offset;
	};
}
