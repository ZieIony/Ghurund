#pragma once

#include "core/math/MathUtils.h"
#include "Interpolator.h"

#include <algorithm>
#include <memory>

namespace Ghurund::UI {
	using namespace Ghurund::Core;

	class Animation {
	private:
		uint64_t duration = 200;
		Interpolator* interpolator = ghnew LinearInterpolator();

	public:
		virtual ~Animation() = 0 {
			delete interpolator;
		}

		inline uint64_t getDuration() const {
			return duration;
		}

		inline void setDuration(uint64_t duration) {
			this->duration = duration;
		}

		__declspec(property(get = getDuration, put = setDuration)) uint64_t Duration;

		inline void setInterpolator(std::unique_ptr<Interpolator> interpolator) {
			delete this->interpolator;
			this->interpolator = interpolator.release();
		}

		inline const Interpolator* getInterpolator() const {
			return interpolator;
		}

		__declspec(property(get = getInterpolator, put = setInterpolator)) Interpolator* Interpolator;
	};

	template<typename Type>
	class ValueAnimation:public Animation {
	private:
		Type initial, target;

	public:
		inline Type getInitialValue() const {
			return initial;
		}

		inline void setInitialValue(Type value) {
			initial = value;
		}

		__declspec(property(get = getInitialValue, put = setInitialValue)) Type InitialValue;

		inline Type getTargetValue() const {
			return target;
		}

		inline void setTargetValue(Type value) {
			target = value;
		}

		__declspec(property(get = getTargetValue, put = setTargetValue)) Type TargetValue;
	};
}