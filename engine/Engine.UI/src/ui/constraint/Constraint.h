#pragma once

#include "core/SharedPointer.h"
#include "core/collection/Set.h"

namespace Ghurund::UI {
	class Control;
	class ConstraintGraph;

	using namespace Ghurund::Core;

	class Constraint:public Pointer {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();
#pragma endregion

	protected:
		float value = 0.0f;
		bool constant = false, skipDependencies = false;
		Set<Constraint*> dependencies;

		virtual bool equalsImpl(const Object& other) const override;

		Constraint(const Constraint& other):
			value(other.value),
			constant(other.constant),
			skipDependencies(other.skipDependencies),
			dependencies(other.dependencies) {}

	public:
		Constraint() {}

		Constraint(bool constant, bool skipDependencies):constant(constant), skipDependencies(skipDependencies) {}

		virtual ~Constraint()// = 0 
		{}

		inline bool isConstant() const {
			return constant;
		}

		__declspec(property(get = isConstant)) bool Constant;

		virtual void resolve(Control& control, ConstraintGraph& graph) {}

		virtual void evaluate() {}

		Set<Constraint*>& getDependencies() {
			return dependencies;
		}

		__declspec(property(get = getDependencies)) Set<Constraint*>& Dependencies;

		inline void setValue(float value) {
			this->value = value;
		}

		inline float getValue() const {
			return value;
		}

		__declspec(property(get = getValue)) float Value;

		// for example wrap constraint can skip fill dependencies to not introduce cycles
		inline bool canSkipDependencies() const {
			return skipDependencies;
		}

		__declspec(property(get = canSkipDependencies)) bool CanSkipDependencies;

		virtual Object* clone() const {
			return ghnew Constraint(*this);
		}
	};
}
