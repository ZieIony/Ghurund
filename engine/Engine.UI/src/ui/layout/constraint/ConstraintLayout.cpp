#include "ghuipch.h"
#include "ConstraintLayout.h"

#include "ui/loading/LayoutLoader.h"
#include "ui/layout/constraint/Constraint.h"
#include <core/collection/Set.h>

namespace Ghurund::UI {
    void ConstraintLayout::onContextChanged() {
        __super::onContextChanged();
        if (Context) {
            Array<float> dashes = { 3.0f, 4.0f };
            strokeStyle.reset(Context->makeStrokeStyle(dashes));
        }
    }

    void ConstraintLayout::onMeasure(float parentWidth, float parentHeight) {
        __super::onMeasure(parentWidth, parentHeight);
        if (!constraintsResolved)
            resolveConstraints();

        for (Constraint* c : sorted)
            c->evaluate();
    }

    void ConstraintLayout::onLayout(float x, float y, float width, float height) {
        __super::onLayout(x, y, width, height);
        for (Control* control : Children) {
            control->layout(x, y, control->MeasuredSize.Width, control->MeasuredSize.Height);
        }
    }

    void ConstraintLayout::load(LayoutLoader& loader, const tinyxml2::XMLElement& xml) {
        __super::load(loader, xml);
        const tinyxml2::XMLElement* child = xml.FirstChildElement();
        while (child != nullptr) {
            if (strcmp(child->Name(), "Guide") == 0)
                guides.add(Guide::load(*child));
            child = child->NextSiblingElement();
        }
        resolveConstraints();
    }

    void ConstraintLayout::onDraw(ICanvas& canvas) {
        __super::onDraw(canvas);
        Color color = Color(0x7f0000ff);
        for (Guide& guide : guides) {
            float position = guide.Value;
            if (guide.side == Side::TOP || guide.side == Side::BOTTOM) {
                canvas.drawLine(0, position, Size.Width, position, color, 1.0f, strokeStyle.get());
            } else {
                canvas.drawLine(position, 0, position, Size.Height, color, 1.0f, strokeStyle.get());
            }
        }
    }

    void ConstraintLayout::resolveConstraints() {
        List<Constraint*> constraints;
        resolveConstraints(constraints);
        sortConstraints(constraints);
        constraintsResolved = true;
    }

    void ConstraintLayout::resolveConstraints(List<Constraint*>& constraints) {
        __super::resolveConstraints(constraints);
        for (Guide& guide : guides)
            guide.resolve(*this);
        for (Guide& guide : guides) {
            if (guide.positionConstraint)
                constraints.add(guide.positionConstraint);
            if (guide.sizeConstraint)
                constraints.add(guide.sizeConstraint);
        }
    }

    void ConstraintLayout::sortConstraints(List<Constraint*>& constraints) {
        Set<Constraint*> noIncoming;
        Map<Constraint*, Set<Constraint*>> connections;
        Map<Constraint*, Set<Constraint*>> reverseConnections;

        auto addConstraint = [&](Constraint& constraint) {
            auto deps = Set<Constraint*>();
            auto& cDeps = constraint.Dependencies;
            if (cDeps.Empty) {
                noIncoming.add(&constraint);
            } else {
                for (auto& dep : cDeps) {
                    deps.add(dep);
                    if (reverseConnections.containsKey(dep)) {
                        reverseConnections.get(dep).add(&constraint);
                    } else {
                        auto dependants = Set<Constraint*>();
                        dependants.add(&constraint);
                        reverseConnections.set(dep, dependants);
                    }
                }
                connections.set(&constraint, deps);
            }
        };

        for (Constraint* c : constraints)
            addConstraint(*c);

        while (!noIncoming.Empty) {
            Constraint* constraint = *noIncoming.begin();
            noIncoming.remove(constraint);
            sorted.add(constraint);
            auto& dependants = constraint->Dependencies;
            for (auto& dep : dependants) {
                auto& connectionsSet = reverseConnections.get(dep);
                if (connectionsSet.Size == 1) {
                    connections.remove(dep);
                    noIncoming.add(dep);
                } else {
                    connectionsSet.remove(constraint);
                }
            }
        }

        if (!connections.Empty)
            throw InvalidStateException("Constraints have a cyclic dependency.");
    }

    const Ghurund::Core::Type& ConstraintLayout::GET_TYPE() {
        static const auto CONSTRUCTOR = Constructor<ConstraintLayout>();
        static const Ghurund::Core::Type TYPE = TypeBuilder<ConstraintLayout>(Ghurund::UI::NAMESPACE_NAME, GH_STRINGIFY(ConstraintLayout))
            .withConstructor(CONSTRUCTOR)
            .withSupertype(__super::GET_TYPE());

        return TYPE;
    }
}
