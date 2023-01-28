#pragma once

#include "Constraint.h"
#include "core/Exceptions.h"
#include "core/collection/List.h"
#include "core/collection/Stack.h"
#include "core/collection/Tree.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ConstraintGraph {
    private:
        List<Constraint*> constraints;

        void sort(List<Constraint*>& sorted, Tree<Constraint*>& visited, Stack<Constraint*>& stack, Constraint* current);

        void sort(List<Constraint*>& sorted, Tree<Constraint*>& visited, Stack<Constraint*>& stack, Constraint* current, bool hadSoftDep);

    public:
        inline void add(Constraint* constraint) {
            if (!constraint->Constant)
                constraints.add(constraint);
        }

        inline void addAll(const std::initializer_list<Constraint*>& constraints) {
            this->constraints.addAll(constraints);
        }

        inline void addAll(const List<Constraint*>& constraints) {
            this->constraints.addAll(constraints);
        }

        inline void clear() {
            constraints.clear();
        }

        inline const Constraint& get(size_t i) const {
            return *constraints[i];
        }

        inline const Constraint& operator[](size_t i) const {
            return *constraints[i];
        }

        inline size_t getSize() const {
            return constraints.Size;
        }

        __declspec(property(get = getSize)) size_t Size;

        void sort();

        inline void evaluate() {
            for (Constraint* c : constraints)
                c->reset();
            for (Constraint* c : constraints)
                c->evaluate();
        }
    };
}
