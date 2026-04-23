#pragma once

#include "core/object/RefCountedObject.h"

namespace Ghurund::Engine {
	using namespace Ghurund::Core;

	class Animation:public RefCountedObject {
#pragma region reflection
	protected:
		virtual const Ghurund::Core::Type& getTypeImpl() const override {
			return GET_TYPE();
		}

	public:
		static const Ghurund::Core::Type& GET_TYPE();

		inline static const Ghurund::Core::Type& TYPE = Animation::GET_TYPE();
#pragma endregion

	private:
		WString* name = nullptr;
		bool islooped = true;

	public:
		~Animation() {
			delete name;
		}

		inline const Ghurund::Core::WString* getName() const {
			return name;
		}

		inline void setName(const WString* name) {
			if (this->name)
				delete this->name;
			if (name)
				this->name = ghnew WString(*name);
		}

		inline void setName(const WString& name) {
			if (this->name)
				delete this->name;
			this->name = ghnew WString(name);
		}

		__declspec(property(get = getName, put = setName)) const Ghurund::Core::WString* Name;

		inline bool getIsLooped() const {
			return islooped;
		}

		inline void setIsLooped(bool islooped) {
			this->islooped = islooped;
		}

		__declspec(property(get = getIsLooped, put = setIsLooped)) bool IsLooped;
	};
}
