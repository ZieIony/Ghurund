#pragma once

#include "core/resource/Resource.h"
#include "core/reflection/TypeBuilder.h"

namespace UnitTest {
	class TestResource:public Ghurund::Core::Resource {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE() {
            static const auto CONSTRUCTOR = Ghurund::Core::Constructor<TestResource>();

            static const Ghurund::Core::Type TYPE = Ghurund::Core::TypeBuilder<TestResource>("UnitTest", GH_STRINGIFY(TestResource))
                .withConstructor(CONSTRUCTOR)
                .withSupertype(__super::GET_TYPE());

            return TYPE;
        }

        inline static const Ghurund::Core::Type& TYPE = TestResource::GET_TYPE();
#pragma endregion

    public:
		Ghurund::Core::AString text;
	};
}