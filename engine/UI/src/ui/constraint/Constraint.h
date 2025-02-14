#pragma once

#include "core/IntrusivePointer.h"
#include "core/collection/Set.h"

namespace Ghurund::UI {
	class Control;
	class ConstraintGraph;
	class ICanvas;

	using namespace Ghurund::Core;

	class Constraint:public RefCountedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

	protected:
#ifdef _DEBUG
		bool firstEvaluation = true;
#endif

		float value = 0.0f;
		bool constant = false, skipDependencies = false, resolved = false, evaluated = false;
		Set<Constraint*> dependencies;

		virtual bool equalsImpl(const Object& other) const override;

		Constraint(const Constraint& other):
			value(other.value),
			constant(other.constant),
			skipDependencies(other.skipDependencies),
			dependencies(other.dependencies) {}

		virtual ~Constraint() = 0 {}

	public:
		Constraint(bool constant, bool skipDependencies):constant(constant), skipDependencies(skipDependencies) {}

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

		virtual float getPreferredMax() const {
			return std::numeric_limits<float>::max();
		}

		__declspec(property(get = getPreferredMax)) float PreferredMax;

		// for example wrap constraint can skip fill dependencies to not introduce cycles
		inline bool canSkipDependencies() const {
			return skipDependencies;
		}

		__declspec(property(get = canSkipDependencies)) bool CanSkipDependencies;

		inline bool isEvaluated() const {
			return evaluated;
		}

		__declspec(property(get = isEvaluated)) bool Evaluated;

		virtual String toString() const override;

#ifdef _DEBUG
		virtual void draw(ICanvas& canvas, float x, float y, float width, float height) const {
			if (skipDependencies)
				return;
			for (Constraint* constraint : dependencies)
				constraint->draw(canvas, x, y, width, height);
		}
#endif
	};
}
