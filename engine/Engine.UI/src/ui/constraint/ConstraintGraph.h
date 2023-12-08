#pragma once

#include "Constraint.h"
#include "core/Exceptions.h"
#include "core/collection/List.h"
#include "core/collection/Stack.h"
#include "core/collection/Set.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ConstraintGraph {
    private:
        List<Constraint*> constraints;

        bool sort(List<Constraint*>& sorted, Set<Constraint*>& visited, Stack<Constraint*>& stack, Constraint* current, bool hadSoftDep);

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

#ifdef _DEBUG
        inline bool validateOrder(const std::initializer_list<Constraint*>& constraints) const {
            size_t index = 0;
            for (Constraint* constraint : constraints) {
                size_t newIndex = this->constraints.indexOf(constraint);
                if (newIndex < index || newIndex == this->constraints.Size)
                    return false;
                index = newIndex;
            }
            return true;
        }
#endif

        inline size_t getSize() const {
            return constraints.Size;
        }

        __declspec(property(get = getSize)) size_t Size;

        void sort();

        inline void evaluate() {
            for (Constraint* c : constraints)
                c->evaluate();
        }

#ifdef _DEBUG
        String print() const;
#endif
    };
}
