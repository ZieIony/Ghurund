#pragma once

#include "core/object/RefCountedObject.h"

namespace Ghurund::Core {
	using namespace Ghurund::Core;

	class Feature:public RefCountedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Feature::GET_TYPE();
#pragma endregion

	private:
		bool initialized = false;

	protected:
		virtual void onInit() {}
		virtual void onUninit() {}

	public:
		virtual ~Feature() {
			uninit();
		}

		void init() {
			if (initialized)
				return;
			onInit();
			initialized = true;
		}

		void uninit() {
			if (!initialized)
				return;
			onUninit();
			initialized = false;
		}

		inline bool isInitialized() const {
			return initialized;
		}

		__declspec(property(get = isInitialized)) bool Initialized;
	};
}