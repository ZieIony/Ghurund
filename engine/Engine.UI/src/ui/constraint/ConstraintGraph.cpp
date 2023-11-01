#include "ghuipch.h"
#include "ConstraintGraph.h"

namespace Ghurund::UI {
    void ConstraintGraph::sort(List<Constraint*>& sorted, Set<Constraint*>& visited, Stack<Constraint*>& stack, Constraint* current) {
        if (visited.contains(current))
            return;
        stack.push(current);
        for (Constraint* dep : current->Dependencies) {
            if (visited.contains(dep))
                continue;
            stack.push(dep);
            sort(sorted, visited, stack, dep, current->CanSkipDependencies);
            stack.pop();
        }
        stack.clear();
        visited.put(current);
        sorted.add(current);
    }
    
    void ConstraintGraph::sort(List<Constraint*>& sorted, Set<Constraint*>& visited, Stack<Constraint*>& stack, Constraint* current, bool hadSoftDep) {
        for (Constraint* dep : current->Dependencies) {
            if (visited.contains(dep)) {
                continue;
            } else if (!stack.contains(dep)) {
                stack.push(dep);
                sort(sorted, visited, stack, dep, hadSoftDep || current->CanSkipDependencies);
                stack.pop();
            } else if (current->CanSkipDependencies) {
                continue;
            } else if (!hadSoftDep) {
                throw InvalidDataException();
            } else {
                return;
            }
        }
        visited.put(current);
        sorted.add(current);
    }
    
    void ConstraintGraph::sort() {
        List<Constraint*> sorted(constraints.Size);
        Set<Constraint*> visited;
        Stack<Constraint*> stack;
        for (Constraint* dep : constraints) {
            if (dep->Dependencies.Empty) {
                sorted.add(dep);
                visited.put(dep);
            } else {
                sort(sorted, visited, stack, dep);
            }
        }
        constraints = sorted;
    }
}
