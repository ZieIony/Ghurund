#include "ghuipch.h"
#include "Constraint.h"
#include "OffsetConstraint.h"
#include "RatioConstraint.h"
#include "MinMaxConstraint.h"

#include "core/reflection/TypeBuilder.h"

namespace Ghurund::UI {
	const Ghurund::Core::Type& Constraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<Constraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	bool Constraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const Constraint& c = (const Constraint&)other;
		return value == c.value && constant == c.constant && skipDependencies == c.skipDependencies && dependencies == c.dependencies;
	}

	String Constraint::toString() const {
		String str = std::format(_T("{} value: {} {}\n"), Type.Name, value, constant ? _T("c") : _T("")).c_str();
		size_t len = 4;
		for (Constraint* dep : dependencies) {
			auto depStr = [&] {
				if (dep->skipDependencies) {
					return String(std::format(
						_T("{} value: {}, deps: {} {}\n"),
						dep->Type.Name,
						value,
						dep->Dependencies.Size,
						constant ? _T("c") : _T("")
					).c_str());
				} else {
					return dep->toString();
				}
			}();
			auto depStrArr = depStr.split(_T("\n"));
			for (size_t j = 0; j < len; j++)
				str.add(_T(" "));
			str.add(_T("\\- "));
			str.add(depStrArr[0]);
			for (size_t i = 1; i < depStrArr.Size; i++) {
				str.add(_T("\n"));
				for (size_t j = 0; j < len; j++)
					str.add(_T(" "));
				str.add(dep != *dependencies.rbegin() ? _T("| ") : _T("  "));
				str.add(depStrArr[i]);
			}
			str.add(_T("\n"));
		}
		return str;
	}

	const Ghurund::Core::Type& OffsetConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<OffsetConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	bool OffsetConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const OffsetConstraint& c = (const OffsetConstraint&)other;
		return offset == c.offset;
	}

	const Ghurund::Core::Type& RatioConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<RatioConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	bool RatioConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const RatioConstraint& c = (const RatioConstraint&)other;
		return ratio == c.ratio;
	}

	const Ghurund::Core::Type& MinMaxConstraint::GET_TYPE() {
		static const Ghurund::Core::Type TYPE = TypeBuilder<MinMaxConstraint>()
			.withSupertype(__super::GET_TYPE());

		return TYPE;
	}

	bool MinMaxConstraint::equalsImpl(const Object& other) const {
		if (__super::equalsImpl(other))
			return true;
		const MinMaxConstraint& c = (const MinMaxConstraint&)other;
		return min == c.min && max == c.max;
	}
}