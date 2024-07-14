#pragma once

#include "TextLayout.h"
#include "ui/constraint/ConstraintGraph.h"

namespace Ghurund::UI {
    class TextLayoutWidthConstraint:public Constraint {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = TextLayoutWidthConstraint::GET_TYPE();
#pragma endregion

    private:
        TextLayout& textLayout;

    protected:
        TextLayoutWidthConstraint(const TextLayoutWidthConstraint& other):Constraint(other), textLayout(other.textLayout) {}

        virtual bool equalsImpl(const Object& other) const override;

    public:
        TextLayoutWidthConstraint(TextLayout& textLayout):textLayout(textLayout) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override {
            evaluated = false;
        }

        virtual void evaluate() override {
            value = (float)textLayout.measureWidth();
            evaluated = true;
        }

        virtual TextLayoutWidthConstraint* clone() const {
            return ghnew TextLayoutWidthConstraint(*this);
        }
    };

    class TextLayoutHeightConstraint:public Constraint {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = TextLayoutHeightConstraint::GET_TYPE();
#pragma endregion

    private:
        TextLayout& textLayout;

    protected:
        TextLayoutHeightConstraint(const TextLayoutHeightConstraint& other):Constraint(other), textLayout(other.textLayout) {}

        virtual bool equalsImpl(const Object& other) const override;

    public:
        TextLayoutHeightConstraint(TextLayout& textLayout):textLayout(textLayout) {}

        virtual void resolve(Control& control, ConstraintGraph& graph) override {
            evaluated = false;
        }

        virtual void evaluate() override {
            value = (float)textLayout.measureHeight();
            evaluated = true;
        }

        virtual TextLayoutHeightConstraint* clone() const {
            return ghnew TextLayoutHeightConstraint(*this);
        }
    };
}