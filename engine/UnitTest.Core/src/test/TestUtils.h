#pragma once

#include "CppUnitTest.h"

#include "core/math/Point.h"
#include "core/math/Size.h"
#include "core/string/TextConversionUtils.h"
#include "TestLogOutput.h"
#include "core/RefCountedObject.h"

#include <format>
#include <initializer_list>

namespace Microsoft::VisualStudio::CppUnitTestFramework {
	template<>
	static std::wstring ToString<Ghurund::Core::FloatSize>(const Ghurund::Core::FloatSize& t) {
		return std::format(L"{}", t);
	}

	template<>
	static std::wstring ToString<Ghurund::Core::IntSize>(const Ghurund::Core::IntSize& t) {
		return std::format(L"{}", t);
	}

	template<>
	static std::wstring ToString<Ghurund::Core::IntPoint>(const Ghurund::Core::IntPoint& t) {
		return std::format(L"{}", t);
	}

	template<>
	static std::wstring ToString<Ghurund::Core::AString>(const Ghurund::Core::AString& t) {
		return Ghurund::Core::convertText<char, wchar_t>(t).Data;
	}

	template<>
	static std::wstring ToString<Ghurund::Core::WString>(const Ghurund::Core::WString& t) {
		return t.Data;
	}

	template<typename T, typename R>
	static void AssertIsType(R* actual, const wchar_t* message = nullptr, const __LineInfo* pLineInfo = nullptr) {
		Assert::IsNotNull(dynamic_cast<T*>(actual), message, pLineInfo);
	}

	template<typename T, typename R>
	static void AssertIsType(R& actual, const wchar_t* message = nullptr, const __LineInfo* pLineInfo = nullptr) {
		try {
			T& cast = dynamic_cast<T&>(actual);
		} catch (std::bad_cast) {
			Assert::Fail(message, pLineInfo);
		}
	}
}

namespace UnitTest::Utils {
	using namespace Ghurund::Core;
	using namespace Microsoft::VisualStudio::CppUnitTestFramework;

	struct TestUtils {
		static void testClassInitialize() {
#ifdef _DEBUG
			RefCountedObject::reservePointers(500);
#endif
			Ghurund::Core::Logger::init(std::make_unique<TestLogOutput>());
			TestLogOutput::initReportHook();
		}

		static void testMethodCleanup() {
#ifdef _DEBUG
			if (RefCountedObject::numberOfAllocatedPointers() > 0) {
				RefCountedObject::dumpPointers();
				RefCountedObject::clearPointers();
				Assert::Fail();
			}
#endif
		}
	};

	template<typename Value, typename Collection>
	bool collectionContains(const Collection& collection, const std::initializer_list<Value>& list) {
		for (const Value& item : list) {
			if (!collection.contains(item))
				return false;
		}
		return true;
	}

	template<typename Collection, typename Collection2>
	bool collectionContains(const Collection& collection, const Collection2& collection2) {
		for (const auto& item : collection2) {
			if (!collection.contains(item))
				return false;
		}
		return true;
	}

	template<typename Value, typename Collection>
	bool collectionsEqual(const Collection& collection, const std::initializer_list<Value>& list) {
		const auto& iterator = collection.begin();
		const Value& iterator2 = list.begin();
		for (; iterator != collection.end(), iterator2 != list.end(); iterator++, iterator2++) {
			if (*iterator != *iterator2)
				return false;
		}
		return true;
	}

	template<typename Collection, typename Collection2>
	bool collectionsEqual(const Collection& collection, const Collection2& collection2) {
		auto iterator = collection.begin();
		auto iterator2 = collection2.begin();
		for (; iterator != collection.end(), iterator2 != collection2.end(); ++iterator, ++iterator2) {
			if (*iterator != *iterator2)
				return false;
		}
		return true;
	}
}