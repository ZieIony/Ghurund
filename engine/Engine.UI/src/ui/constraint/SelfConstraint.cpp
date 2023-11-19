#include "ghuipch.h"
#include "SelfConstraint.h"

#include "ui/constraint/ConstraintGraph.h"
#include "ui/control/Control.h"

namespace Ghurund::UI {
    void SelfWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.put(&control.Width);
        graph.add(this);
    }

    void SelfHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        dependencies.clear();
        dependencies.put(&control.Height);
        graph.add(this);
    }

    bool CenterLeftConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const CenterLeftConstraint& c = (const CenterLeftConstraint&)other;
        return left == c.left && width == c.width && right == c.right;
    }

    void CenterLeftConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        left->resolve(control, graph);
        width->resolve(control, graph);
        right->resolve(control, graph);
    }

    bool CenterRightConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const CenterRightConstraint& c = (const CenterRightConstraint&)other;
        return left == c.left && width == c.width && right == c.right;
    }

    void CenterRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        left->resolve(control, graph);
        width->resolve(control, graph);
        right->resolve(control, graph);
    }

    bool CenterTopConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const CenterTopConstraint& c = (const CenterTopConstraint&)other;
        return top == c.top && height == c.height && bottom == c.bottom;
    }

    void CenterTopConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        top->resolve(control, graph);
        height->resolve(control, graph);
        bottom->resolve(control, graph);
    }

    bool CenterBottomConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const CenterBottomConstraint& c = (const CenterBottomConstraint&)other;
        return top == c.top && height == c.height && bottom == c.bottom;
    }

    void CenterBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        top->resolve(control, graph);
        height->resolve(control, graph);
        bottom->resolve(control, graph);
    }

    bool LeftWidthConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const LeftWidthConstraint& c = (const LeftWidthConstraint&)other;
        return left == c.left && width == c.width;
    }

    void LeftWidthConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        left->resolve(control, graph);
        width->resolve(control, graph);
    }

    bool LeftRightConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const LeftRightConstraint& c = (const LeftRightConstraint&)other;
        return left == c.left && right == c.right;
    }

    void LeftRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        left->resolve(control, graph);
        right->resolve(control, graph);
    }

    bool WidthRightConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const WidthRightConstraint& c = (const WidthRightConstraint&)other;
        return width == c.width && right == c.right;
    }

    void WidthRightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        width->resolve(control, graph);
        right->resolve(control, graph);
    }

    bool TopHeightConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const TopHeightConstraint& c = (const TopHeightConstraint&)other;
        return top == c.top && height == c.height;
    }

    void TopHeightConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        top->resolve(control, graph);
        height->resolve(control, graph);
    }

    bool TopBottomConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const TopBottomConstraint& c = (const TopBottomConstraint&)other;
        return top == c.top && bottom == c.bottom;
    }

    void TopBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        top->resolve(control, graph);
        bottom->resolve(control, graph);
    }

    bool HeightBottomConstraint::equalsImpl(const Object& other) const {
        if (__super::equalsImpl(other))
            return true;
        const HeightBottomConstraint& c = (const HeightBottomConstraint&)other;
        return height == c.height && bottom == c.bottom;
    }

    void HeightBottomConstraint::resolve(Control& control, ConstraintGraph& graph) {
        graph.add(this);
        height->resolve(control, graph);
        bottom->resolve(control, graph);
    }
}