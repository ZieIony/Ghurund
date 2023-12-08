#include "ghuipch.h"
#include "SelfConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
    const Ghurund::Core::Type& SelfWidthConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<SelfWidthConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void SelfWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        evaluated = false;
        dependencies.put(&control.Width);
        graph.add(this);
    }

    const Ghurund::Core::Type& SelfHeightConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<SelfHeightConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    void SelfHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        evaluated = false;
        dependencies.put(&control.Height);
        graph.add(this);
    }

    const Ghurund::Core::Type& CenterLeftConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<CenterLeftConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool CenterLeftConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const CenterLeftConstraint& c = (const CenterLeftConstraint&)other;
        return left == c.left && width == c.width && right == c.right;
    }

    void CenterLeftConstraint::resolve(Control& control, ConstraintGraph& graph) {
        evaluated = false;
        graph.add(this);
        left->resolve(control, graph);
        width->resolve(control, graph);
        right->resolve(control, graph);
    }

    const Ghurund::Core::Type& CenterRightConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<CenterRightConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool CenterRightConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const CenterRightConstraint& c = (const CenterRightConstraint&)other;
        return left == c.left && width == c.width && right == c.right;
    }

    void CenterRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        evaluated = false;
        graph.add(this);
        left->resolve(control, graph);
        width->resolve(control, graph);
        right->resolve(control, graph);
    }

    const Ghurund::Core::Type& CenterTopConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<CenterTopConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool CenterTopConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const CenterTopConstraint& c = (const CenterTopConstraint&)other;
        return top == c.top && height == c.height && bottom == c.bottom;
    }

    void CenterTopConstraint::resolve(Control& control, ConstraintGraph& graph) {
        evaluated = false;
        graph.add(this);
        top->resolve(control, graph);
        height->resolve(control, graph);
        bottom->resolve(control, graph);
    }

    const Ghurund::Core::Type& CenterBottomConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<CenterBottomConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool CenterBottomConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const CenterBottomConstraint& c = (const CenterBottomConstraint&)other;
        return top == c.top && height == c.height && bottom == c.bottom;
    }

    void CenterBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
        evaluated = false;
        graph.add(this);
        top->resolve(control, graph);
        height->resolve(control, graph);
        bottom->resolve(control, graph);
    }

    const Ghurund::Core::Type& LeftWidthConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<LeftWidthConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool LeftWidthConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const LeftWidthConstraint& c = (const LeftWidthConstraint&)other;
        return left == c.left && width == c.width;
    }

    void LeftWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
        evaluated = false;
        graph.add(this);
        left->resolve(control, graph);
        width->resolve(control, graph);
    }

    const Ghurund::Core::Type& LeftRightConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<LeftRightConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool LeftRightConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const LeftRightConstraint& c = (const LeftRightConstraint&)other;
        return left == c.left && right == c.right;
    }

    void LeftRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        evaluated = false;
        graph.add(this);
        left->resolve(control, graph);
        right->resolve(control, graph);
    }

    const Ghurund::Core::Type& WidthRightConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<WidthRightConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool WidthRightConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const WidthRightConstraint& c = (const WidthRightConstraint&)other;
        return width == c.width && right == c.right;
    }

    void WidthRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        evaluated = false;
        graph.add(this);
        width->resolve(control, graph);
        right->resolve(control, graph);
    }

    const Ghurund::Core::Type& TopHeightConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<TopHeightConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool TopHeightConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const TopHeightConstraint& c = (const TopHeightConstraint&)other;
        return top == c.top && height == c.height;
    }

    void TopHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        evaluated = false;
        graph.add(this);
        top->resolve(control, graph);
        height->resolve(control, graph);
    }

    const Ghurund::Core::Type& TopBottomConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<TopBottomConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool TopBottomConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const TopBottomConstraint& c = (const TopBottomConstraint&)other;
        return top == c.top && bottom == c.bottom;
    }

    void TopBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
        evaluated = false;
        graph.add(this);
        top->resolve(control, graph);
        bottom->resolve(control, graph);
    }

    const Ghurund::Core::Type& HeightBottomConstraint::GET_TYPE() {
        static const Ghurund::Core::Type TYPE = TypeBuilder<HeightBottomConstraint>()
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }

    bool HeightBottomConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const HeightBottomConstraint& c = (const HeightBottomConstraint&)other;
        return height == c.height && bottom == c.bottom;
    }

    void HeightBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
        evaluated = false;
        graph.add(this);
        height->resolve(control, graph);
        bottom->resolve(control, graph);
    }
}