#pragma once

#include "MinMaxConstraint.h"
#include "ValueConstraint.h"
#include "core/math/MathUtils.h"

namespace Ghurund::UI {
	class Control;

	class SelfWidthConstraint:public MinMaxConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = SelfWidthConstraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
			evaluated = true;
		}

		virtual SelfWidthConstraint* clone() const {
			return ghnew SelfWidthConstraint(*this);
		}
	};

	class SelfHeightConstraint:public MinMaxConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = SelfHeightConstraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = minMax(min, (*dependencies.begin())->Value * ratio + offset, max);
			evaluated = true;
		}

		virtual SelfHeightConstraint* clone() const {
			return ghnew SelfHeightConstraint(*this);
		}
	};

	class LeftWidthConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = LeftWidthConstraint::GET_TYPE();
#pragma endregion

	private:
		IntrusivePointer<Constraint> left, width;

		LeftWidthConstraint(const LeftWidthConstraint& other):Constraint(other), left(other.left), width(other.width) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		LeftWidthConstraint(
			const IntrusivePointer<Constraint>& left,
			const IntrusivePointer<Constraint>& width
		):left(left), width(width) {
			dependencies.putAll({ this->left.get(), this->width.get() });
		}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = left->Value + width->Value;
			evaluated = true;
		}

		virtual LeftWidthConstraint* clone() const {
			return ghnew LeftWidthConstraint(*this);
		}
	};

	class CenterLeftConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = CenterLeftConstraint::GET_TYPE();
#pragma endregion

	private:
		IntrusivePointer<Constraint> left, width, right;

		CenterLeftConstraint(const CenterLeftConstraint& other):Constraint(other), left(other.left), width(other.width), right(other.right) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		CenterLeftConstraint(
			const IntrusivePointer<Constraint>& left,
			const IntrusivePointer<Constraint>& width,
			const IntrusivePointer<Constraint>& right
		):left(left), width(width), right(right) {
			dependencies.putAll({ this->left.get(), this->width.get(), this->right.get() });
		}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = (right->Value + left->Value - width->Value) / 2;
			evaluated = true;
		}

		virtual CenterLeftConstraint* clone() const {
			return ghnew CenterLeftConstraint(*this);
		}
	};

	class LeftRightConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = LeftRightConstraint::GET_TYPE();
#pragma endregion

	private:
		IntrusivePointer<Constraint> left, right;

		LeftRightConstraint(const LeftRightConstraint& other):Constraint(other), left(other.left), right(other.right) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		LeftRightConstraint(
			const IntrusivePointer<Constraint>& left,
			const IntrusivePointer<Constraint>& right
		):left(left), right(right) {
			dependencies.putAll({ this->left.get(), this->right.get() });
		}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = right->Value - left->Value;
			evaluated = true;
		}

		virtual LeftRightConstraint* clone() const {
			return ghnew LeftRightConstraint(*this);
		}
	};

	class CenterRightConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = CenterRightConstraint::GET_TYPE();
#pragma endregion

	private:
		IntrusivePointer<Constraint> left, width, right;

		CenterRightConstraint(const CenterRightConstraint& other):Constraint(other), left(other.left), width(other.width), right(other.right) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		CenterRightConstraint(
			const IntrusivePointer<Constraint>& left,
			const IntrusivePointer<Constraint>& width,
			const IntrusivePointer<Constraint>& right
		):left(left), width(width), right(right) {
			dependencies.putAll({ this->left.get(), this->width.get(), this->right.get() });
		}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = (right->Value + left->Value + width->Value) / 2;
			evaluated = true;
		}

		virtual CenterRightConstraint* clone() const {
			return ghnew CenterRightConstraint(*this);
		}
	};

	class WidthRightConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = WidthRightConstraint::GET_TYPE();
#pragma endregion

	private:
		IntrusivePointer<Constraint> width, right;

		WidthRightConstraint(const WidthRightConstraint& other):Constraint(other), width(other.width), right(other.right) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		WidthRightConstraint(
			const IntrusivePointer<Constraint>& width,
			const IntrusivePointer<Constraint>& right
		):width(width), right(right) {
			dependencies.putAll({ this->width.get(), this->right.get() });
		}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = right->Value - width->Value;
			evaluated = true;
		}

		virtual WidthRightConstraint* clone() const {
			return ghnew WidthRightConstraint(*this);
		}
	};

	class TopHeightConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = TopHeightConstraint::GET_TYPE();
#pragma endregion

	private:
		IntrusivePointer<Constraint> top, height;

		TopHeightConstraint(const TopHeightConstraint& other):Constraint(other), top(other.top), height(other.height) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		TopHeightConstraint(
			const IntrusivePointer<Constraint>& top,
			const IntrusivePointer<Constraint>& height
		):top(top), height(height) {
			dependencies.putAll({ this->top.get(), this->height.get() });
		}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = top->Value + height->Value;
			evaluated = true;
		}

		virtual TopHeightConstraint* clone() const {
			return ghnew TopHeightConstraint(*this);
		}
	};

	class CenterTopConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = CenterTopConstraint::GET_TYPE();
#pragma endregion

	private:
		IntrusivePointer<Constraint> top, height, bottom;

		CenterTopConstraint(const CenterTopConstraint& other):Constraint(other), top(other.top), height(other.height), bottom(other.bottom) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		CenterTopConstraint(
			const IntrusivePointer<Constraint>& top,
			const IntrusivePointer<Constraint>& height,
			const IntrusivePointer<Constraint>& bottom
		):top(top), height(height), bottom(bottom) {
			dependencies.putAll({ this->top.get(), this->height.get(), this->bottom.get() });
		}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = (bottom->Value + top->Value - height->Value) / 2;
			evaluated = true;
		}

		virtual CenterTopConstraint* clone() const {
			return ghnew CenterTopConstraint(*this);
		}
	};

	class TopBottomConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = TopBottomConstraint::GET_TYPE();
#pragma endregion

	private:
		IntrusivePointer<Constraint> top, bottom;

		TopBottomConstraint(const TopBottomConstraint& other):Constraint(other), top(other.top), bottom(other.bottom) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		TopBottomConstraint(
			const IntrusivePointer<Constraint>& top,
			const IntrusivePointer<Constraint>& bottom
		):top(top), bottom(bottom) {
			dependencies.putAll({ this->top.get(), this->bottom.get() });
		}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = bottom->Value - top->Value;
			evaluated = true;
		}

		virtual TopBottomConstraint* clone() const {
			return ghnew TopBottomConstraint(*this);
		}
	};

	class CenterBottomConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = CenterBottomConstraint::GET_TYPE();
#pragma endregion

	private:
		IntrusivePointer<Constraint> top, height, bottom;

		CenterBottomConstraint(const CenterBottomConstraint& other):Constraint(other), top(other.top), height(other.height), bottom(other.bottom) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		CenterBottomConstraint(
			const IntrusivePointer<Constraint>& top,
			const IntrusivePointer<Constraint>& height,
			const IntrusivePointer<Constraint>& bottom
		):top(top), height(height), bottom(bottom) {
			dependencies.putAll({ this->top.get(), this->height.get(), this->bottom.get() });
		}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = (bottom->Value + top->Value + height->Value) / 2;
			evaluated = true;
		}

		virtual CenterBottomConstraint* clone() const {
			return ghnew CenterBottomConstraint(*this);
		}
	};

	class HeightBottomConstraint:public Constraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = HeightBottomConstraint::GET_TYPE();
#pragma endregion

	private:
		IntrusivePointer<Constraint> height, bottom;

		HeightBottomConstraint(const HeightBottomConstraint& other):Constraint(other), height(other.height), bottom(other.bottom) {}

		virtual bool equalsImpl(const Object& other) const override;

	public:
		HeightBottomConstraint(
			const IntrusivePointer<Constraint>& height,
			const IntrusivePointer<Constraint>& bottom
		):height(height), bottom(bottom) {
			dependencies.putAll({ this->height.get(), this->bottom.get() });
		}

		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override {
			value = bottom->Value - height->Value;
			evaluated = true;
		}

		virtual HeightBottomConstraint* clone() const {
			return ghnew HeightBottomConstraint(*this);
		}
	};
}