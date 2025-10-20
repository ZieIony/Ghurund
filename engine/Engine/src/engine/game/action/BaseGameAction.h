#pragma once

#include "core/object/RefCountedObject.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class BaseGameAction:public RefCountedObject {
	protected:
		bool isInProgress = false;

	public:
		inline bool getIsInProgress() const {
			return isInProgress;
		}

		__declspec(property(get = getIsInProgress)) bool IsInProgress;

		inline void cancel() {
			if (isInProgress) {
				isInProgress = false;
				onCancelled();
			}
		}

		virtual void onCancelled() {}
	};

	template<typename T>
	class BaseTypedGameAction:public BaseGameAction {
	private:
		uint64_t startTime;
		T value;

	protected:
		virtual bool getShouldBeInProgress(T value) const = 0;

	public:
		inline T getValue() const {
			return value;
		}

		__declspec(property(get = getValue)) T Value;

		virtual void dispatchEvent(T value, uint64_t time) {
			bool isInProgress = getShouldBeInProgress(value);
			if (!this->isInProgress && isInProgress) {
				startTime = time;
				this->value = value;
				this->isInProgress = isInProgress;
				onStarted();
			} else if (this->isInProgress) {
				if (isInProgress) {
					this->value = value;
					onInProgress(time - startTime);
				} else {
					this->value = value;
					this->isInProgress = isInProgress;
					onFinished(time - startTime);
				}
			}
		}

		virtual void onStarted() {}

		virtual void onInProgress(uint64_t duration) {}

		virtual void onFinished(uint64_t duration) {}
	};
}