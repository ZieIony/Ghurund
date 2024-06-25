#pragma once

#include "OffsetConstraint.h"
#include "ValueConstraint.h"
#include "core/math/MathUtils.h"
#include "ui/control/ControlParent.h"

namespace Ghurund::UI {
	class ParentLeftConstraint:public OffsetConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ParentLeftConstraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override {
			evaluated = false;
		}

		virtual void evaluate() override {
			value = offset;
			evaluated = true;
		}

		virtual ParentLeftConstraint* clone() const {
			return ghnew ParentLeftConstraint(*this);
		}

#ifdef _DEBUG
		virtual void draw(ICanvas& canvas, float x, float y, float width, float height) const;
#endif
	};

	class ParentRightConstraint:public OffsetConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ParentRightConstraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override;

		virtual ParentRightConstraint* clone() const {
			return ghnew ParentRightConstraint(*this);
		}

#ifdef _DEBUG
		virtual void draw(ICanvas& canvas, float x, float y, float width, float height) const;
#endif
	};

	class ParentTopConstraint:public OffsetConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ParentTopConstraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override {
			evaluated = false;
		}

		virtual void evaluate() override {
			value = offset;
			evaluated = true;
		}

		virtual ParentTopConstraint* clone() const {
			return ghnew ParentTopConstraint(*this);
		}

#ifdef _DEBUG
		virtual void draw(ICanvas& canvas, float x, float y, float width, float height) const;
#endif
	};

	class ParentBottomConstraint:public OffsetConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ParentBottomConstraint::GET_TYPE();
#pragma endregion

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override;

		virtual ParentBottomConstraint* clone() const {
			return ghnew ParentBottomConstraint(*this);
		}

#ifdef _DEBUG
		virtual void draw(ICanvas& canvas, float x, float y, float width, float height) const;
#endif
	};

	class ParentWidthConstraint:public MinMaxConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ParentWidthConstraint::GET_TYPE();
#pragma endregion

	private:
		SharedPointer<Constraint> parentWidth, contentWidth;

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override;

		virtual ParentWidthConstraint* clone() const {
			return ghnew ParentWidthConstraint(*this);
		}
	};

	class ParentHeightConstraint:public MinMaxConstraint {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = ParentHeightConstraint::GET_TYPE();
#pragma endregion

	private:
		SharedPointer<Constraint> parentHeight, contentHeight;

	public:
		virtual void resolve(Control& control, ConstraintGraph& graph) override;

		virtual void evaluate() override;

		virtual ParentHeightConstraint* clone() const {
			return ghnew ParentHeightConstraint(*this);
		}
	};
}