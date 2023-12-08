#pragma once

#include "OffsetConstraint.h"
#include "ValueConstraint.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
	class SiblingLeftConstraint:public OffsetConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

	private:
		const AString name;

	protected:
		SiblingLeftConstraint(const SiblingLeftConstraint& other):OffsetConstraint(other), name(other.name) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		SiblingLeftConstraint(const AString& name):name(name) {}

		inline const AString& getName() const {
			return name;
		}

		__declspec(property(get = getName)) const AString& Name;

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value + offset;
			} else {
				value = offset;
			}
			evaluated = true;
		}

		virtual Object* clone() const {
			return ghnew SiblingLeftConstraint(*this);
		}
	};

	class SiblingRightConstraint:public OffsetConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

	private:
		const AString name;

	protected:
		SiblingRightConstraint(const SiblingRightConstraint& other):OffsetConstraint(other), name(other.name) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		SiblingRightConstraint(const AString& name):name(name) {}

		inline const AString& getName() const {
			return name;
		}

		__declspec(property(get = getName)) const AString& Name;

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value + offset;
			} else {
				value = offset;
			}
			evaluated = true;
		}

		virtual Object* clone() const {
			return ghnew SiblingRightConstraint(*this);
		}
	};

	class SiblingTopConstraint: public OffsetConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

	private:
		const AString name;

	protected:
		SiblingTopConstraint(const SiblingTopConstraint& other):OffsetConstraint(other), name(other.name) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		SiblingTopConstraint(const AString& name): name(name) {}

		inline const AString& getName() const {
			return name;
		}

		__declspec(property(get = getName)) const AString& Name;

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value + offset;
			} else {
				value = offset;
			}
			evaluated = true;
		}

		virtual Object* clone() const {
			return ghnew SiblingTopConstraint(*this);
		}
	};

	class SiblingBottomConstraint:public OffsetConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

	private:
		const AString name;

	protected:
		SiblingBottomConstraint(const SiblingBottomConstraint& other):OffsetConstraint(other), name(other.name) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		SiblingBottomConstraint(const AString& name):name(name) {}

		inline const AString& getName() const {
			return name;
		}

		__declspec(property(get = getName)) const AString& Name;

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = (*dependencies.begin())->Value + offset;
			} else {
				value = offset;
			}
			evaluated = true;
		}

		virtual Object* clone() const {
			return ghnew SiblingBottomConstraint(*this);
		}
	};

	class SiblingWidthConstraint:public MinMaxConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

	private:
		const AString name;

	protected:
		SiblingWidthConstraint(const SiblingWidthConstraint& other):MinMaxConstraint(other), name(other.name) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		SiblingWidthConstraint(const AString& name):name(name) {}

		inline const AString& getName() const {
			return name;
		}

		__declspec(property(get = getName)) const AString& Name;

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
			} else {
				value = minMax(min, offset, max);
			}
			evaluated = true;
		}

		virtual Object* clone() const {
			return ghnew SiblingWidthConstraint(*this);
		}
	};

	class SiblingHeightConstraint:public MinMaxConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Constraint::GET_TYPE();
#pragma endregion

	private:
		const AString name;

	protected:
		SiblingHeightConstraint(const SiblingHeightConstraint& other):MinMaxConstraint(other), name(other.name) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		SiblingHeightConstraint(const AString& name): name(name) {}

		inline const AString& getName() const {
			return name;
		}

		__declspec(property(get = getName)) const AString& Name;

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			if (!dependencies.Empty) {
				value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
			} else {
				value = minMax(min, offset, max);
			}
			evaluated = true;
		}

		virtual Object* clone() const {
			return ghnew SiblingHeightConstraint(*this);
		}
	};
}