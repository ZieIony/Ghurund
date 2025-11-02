#pragma once

#include "core/object/RefCountedObject.h"
#include "core/string/String.h"
#include "core/object/IntrusivePointer.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class ParameterCollection;

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
        const AString name;
        void* rawValue = nullptr;
        bool isEmpty = true;
        IntrusivePointer<Parameter> defaultValue;

    public:
        Parameter(const AString& name):name(name) {}

        const AString& getName() const {
            return name;
        }

        __declspec(property(get = getName)) const AString& Name;

		inline const void* const getRawValue() const {
			if (isEmpty && defaultValue.get())
				return defaultValue->RawValue;
			return rawValue;
		}

		__declspec(property(get = getRawValue)) const void* const RawValue;

        virtual size_t getSize() const = 0;

        __declspec(property(get = getSize)) size_t Size;

        inline bool getIsEmpty() const {
            return isEmpty;
        }

        __declspec(property(get = getIsEmpty)) bool IsEmpty;

        inline Parameter* getDefaultValue() {
            return defaultValue.get();
        }

        void setDefaultValue(Parameter* value) {
            if(value)
				value->addReference();
            defaultValue.set(value);
        }

        __declspec(property(get = getDefaultValue, put = setDefaultValue)) Parameter* DefaultValue;

        void initDefault(ParameterCollection& defaultParameterCollection);
    };
}