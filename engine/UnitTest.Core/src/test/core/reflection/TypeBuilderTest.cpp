#include "utcpch.h"
#include "CppUnitTest.h"

#include "test/MemoryGuard.h"
#include "test/TestClass.h"
#include "test/TestUtils.h"
#include "core/reflection/StandardTypes.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	namespace Test {
		template<typename A>
		class TemplateTestClass {};

		template<typename A, typename B>
		class Template2TestClass {};
	}

	using namespace UnitTest::Utils;
	using namespace Ghurund::Core;

	TEST_CLASS(TypeBuilderTest) {
public:

	TEST_METHOD(autoName) {
		const Type& type = ObjectTestClass::TYPE;
		Assert::AreEqual(AString("ObjectTestClass"), type.Name);
		Assert::AreEqual(AString("UnitTest::Utils"), type.Namespace);
	}

	/*
	TEST_METHOD(autoNameTemplate) {
		const Type type = TypeBuilder<Test::TemplateTestClass<int>>();
		Assert::AreEqual(AString("TemplateTestClass<int>"), type.Name);
		Assert::AreEqual(AString("UnitTest::Test"), type.Namespace);
		auto& templateParam = type.TemplateParams[0].get();
		Assert::AreEqual(AString("int"), templateParam.Name);
		Assert::AreEqual(AString(""), templateParam.Namespace);
	}

	TEST_METHOD(autoNameTemplate2) {
		const Type type = TypeBuilder<Test::Template2TestClass<int, float>>();
		Assert::AreEqual(AString("TemplateTestClass2"), type.Name);
		Assert::AreEqual(AString("UnitTest::Test"), type.Namespace);
		auto& templateParam = type.TemplateParams[0].get();
		Assert::AreEqual(AString("int"), templateParam.Name);
		Assert::AreEqual(AString(""), templateParam.Namespace);
		auto& templateParam2 = type.TemplateParams[1].get();
		Assert::AreEqual(AString("float"), templateParam2.Name);
		Assert::AreEqual(AString(""), templateParam2.Namespace);
	}

	TEST_METHOD(autoNameTemplateMix) {
		const Type type = TypeBuilder<Test::Template2TestClass<Test::TemplateTestClass<int>, float>>();
		Assert::AreEqual(AString("TemplateTestClass2"), type.Name);
		Assert::AreEqual(AString("UnitTest::Test"), type.Namespace);
		auto& templateParam = type.TemplateParams[0].get();
		Assert::AreEqual(AString("TemplateTestClass"), templateParam.Name);
		Assert::AreEqual(AString("UnitTest::Test"), templateParam.Namespace);
		Assert::AreEqual(AString("int"), templateParam.TemplateParams[0].get().Name);
		Assert::AreEqual(AString(""), templateParam.TemplateParams[0].get().Namespace);
		auto& templateParam2 = type.TemplateParams[1].get();
		Assert::AreEqual(AString("float"), templateParam2.Name);
		Assert::AreEqual(AString(""), templateParam2.Namespace);
	}

	TEST_METHOD(autoNameTemplateMix2) {
		const Type type = TypeBuilder<Test::Template2TestClass<int, Test::TemplateTestClass<float>>>();
		Assert::AreEqual(AString("TemplateTestClass2"), type.Name);
		Assert::AreEqual(AString("UnitTest::Test"), type.Namespace);
		auto& templateParam = type.TemplateParams[0].get();
		Assert::AreEqual(AString("int"), templateParam.Name);
		Assert::AreEqual(AString(""), templateParam.Namespace);
		auto& templateParam2 = type.TemplateParams[1].get();
		Assert::AreEqual(AString("TemplateTestClass"), templateParam2.Name);
		Assert::AreEqual(AString("UnitTest::Test"), templateParam2.Namespace);
		Assert::AreEqual(AString("float"), templateParam2.TemplateParams[0].get().Name);
		Assert::AreEqual(AString(""), templateParam2.TemplateParams[0].get().Namespace);
	}
	*/
	};
}
