#include "pch.h"
#include "CppUnitTest.h"

#include "core/resource/ResourceManager.h"
#include "TestLoader.h"
#include "TestResource.h"
#include "TestLibrary.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace Ghurund::Core;

	TEST_CLASS(ResourceManagerTest) {
private:
	ResourceManager resourceManager;
	SharedPointer<TestLoader> testLoader;

public:
	ResourceManagerTest() {
		testLoader = makeShared<TestLoader>();
		resourceManager.Loaders.set<TestLoader>(testLoader.get());
		resourceManager.Libraries.add(std::make_unique<TestLibrary>());
	}

	TEST_METHOD(ResourceManager_loadFileFromLibrary) {
		resourceManager.clearCache();

		TestLibrary& library = (TestLibrary&)resourceManager.Libraries.get(0);
		size_t getCalls = library.getCalls;
		size_t loadCalls = testLoader->loadCalls;

		SharedPointer<TestResource> resource(resourceManager.load<TestResource>(ResourcePath(L"test", L"testpath"), DirectoryPath()));
		Assert::AreEqual(resource->text, AString("test"));
		Assert::AreEqual(getCalls + 1, library.getCalls);
		Assert::AreEqual(loadCalls + 1, testLoader->loadCalls);
	}

	TEST_METHOD(ResourceManager_loadCached) {
		resourceManager.clearCache();

		TestLibrary& library = (TestLibrary&)resourceManager.Libraries.get(0);
		size_t getCalls = library.getCalls;
		size_t loadCalls = testLoader->loadCalls;

		SharedPointer<TestResource> resource(resourceManager.load<TestResource>(ResourcePath(L"test", L"testpath"), DirectoryPath()));
		Assert::AreEqual(resource->text, AString("test"));
		Assert::AreEqual(getCalls + 1, library.getCalls);
		Assert::AreEqual(loadCalls + 1, testLoader->loadCalls);
	}
	};
}

namespace Microsoft::VisualStudio::CppUnitTestFramework {
	template<> static std::wstring ToString<Ghurund::Core::AString>(const Ghurund::Core::AString& t) {
		return convertText<char, wchar_t>(t).Data;
	}
}