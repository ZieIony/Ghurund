#pragma once

#include "core/Enum.h"

namespace UnitTest::Utils {
	using namespace Ghurund::Core;

	enum class TestEnumEnum {
		A, B
	};

	class TestEnum:public Enum<TestEnumEnum, TestEnum> {
	protected:
		TestEnum(TestEnumEnum value, const char* name, int testValue):Enum<TestEnumEnum, TestEnum>(value, name), testValue(testValue) {
		}

	public:
		int testValue;

		static const TestEnum A, B;

		TestEnum(const TestEnum& other):Enum(other), testValue(other.testValue) {}

		TestEnum(TestEnum&& other) noexcept:Enum(other), testValue(other.testValue) {}

		inline TestEnum& operator=(const TestEnum& other) {
			if (this == &other)
				return *this;
			__super::operator=(other);
			testValue = other.testValue;
			return *this;
		}

		inline TestEnum& operator=(TestEnum&& other) noexcept {
			if (this == &other)
				return *this;
			__super::operator=(std::move(other));
			testValue = other.testValue;
			return *this;
		}
	};
}