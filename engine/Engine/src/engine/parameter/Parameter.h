#pragma once

#include "core/object/RefCountedObject.h"
#include "core/string/String.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class Parameter: public RefCountedObject {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Parameter::GET_TYPE();
#pragma endregion

    protected:
        const AString constantName;
        void* rawValue = nullptr;
        bool empty = true;

    public:
        Parameter(const AString& constantName):constantName(constantName) {}

        const AString& getConstantName() const {
            return constantName;
        }

        __declspec(property(get = getConstantName)) const AString& ConstantName;

		inline const void* const getRawValue() const {
			return rawValue;
		}

		__declspec(property(get = getRawValue)) const void* const RawValue;
    };
}