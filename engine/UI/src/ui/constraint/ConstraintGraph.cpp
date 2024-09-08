#include "ghuipch.h"
#include "ConstraintGraph.h"

namespace Ghurund::UI {
	bool ConstraintGraph::sort(List<Constraint*>& sorted, Set<Constraint*>& visited, Stack<Constraint*>& stack, Constraint* current, bool hadSoftDep) {
		if (visited.contains(current))
			return false;
		// cycle detection
		if (stack.contains(current)) {
			if (hadSoftDep) {
				return true;
			} else {
				throw InvalidDataException("cycle detected where cycles are not allowed");
			}
		}
		bool cycle = false;
		stack.push(current);
		for (Constraint* dep : current->Dependencies)
			cycle |= sort(sorted, visited, stack, dep, hadSoftDep || current->CanSkipDependencies);
		stack.pop();
		// soft dependencies parent breaks cycles
		if (current->CanSkipDependencies)
			cycle = false;
		if (!cycle) {
			visited.put(current);
			sorted.add(current);
		}
		return cycle;
	}

	void ConstraintGraph::sort() {
		List<Constraint*> sorted(constraints.Size);
		Set<Constraint*> visited;
		Stack<Constraint*> stack;
		for (Constraint* dep : constraints)
			sort(sorted, visited, stack, dep, false);
		constraints = sorted;
	}

#ifdef _DEBUG
	String ConstraintGraph::print() const {
		String str;
		for (Constraint* c : constraints)
			str.add(c->toString());
		return str;
	}
#endif
}
