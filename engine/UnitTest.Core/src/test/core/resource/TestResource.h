#pragma once

#include "core/resource/Resource.h"
#include "core/reflection/TypeBuilder.h"

namespace UnitTest {
	class TestResource:public Ghurund::Core::Resource {
	public:
		Ghurund::Core::AString text;

        static const Ghurund::Core::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = Ghurund::Core::Constructor<TestResource>();

            static const Ghurund::Core::Type TYPE = Ghurund::Core::TypeBuilder<TestResource>("UnitTest", GH_STRINGIFY(TestResource))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        virtual const Ghurund::Core::Type& getType() const {
            return GET_TYPE();
        }

        __declspec(property(get = getType)) const Ghurund::Core::Type& Type;
	};
}