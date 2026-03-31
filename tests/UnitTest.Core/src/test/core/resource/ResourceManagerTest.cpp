#include "utcpch.h"
#include "CppUnitTest.h"
#include "TestLoader.h"
#include "TestResource.h"
#include "TestLibrary.h"
#include "test/utils/MemoryGuard.h"

#include "core/resource/ResourceManager.h"
#include "core/string/TextConversionUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace UnitTest::Utils;
	using namespace Ghurund::Core;

	TEST_CLASS(ResourceManagerTest) {
private:
	Timer timer;
	CoroutineThreadPool threadPool = CoroutineThreadPool(4);
	CoroutineScheduler coroutineScheduler = Ghurund::Core::CoroutineScheduler(threadPool, timer);
	ResourceManager resourceManager = coroutineScheduler;
	IntrusivePointer<TestLoader> testLoader;

public:
	ResourceManagerTest() {
		testLoader = makeIntrusive<TestLoader>();
		resourceManager.Loaders.set<TestResource>(*testLoader.get());
		resourceManager.Libraries.add(std::make_unique<TestLibrary>());
	}

	TEST_METHOD(ResourceManager_loadFileFromLibrary) {
		MemoryGuard guard;
		{
			resourceManager.clearCache();

			TestLibrary& library = (TestLibrary&)resourceManager.Libraries.get(0);
			size_t getCalls = library.getCalls;
			size_t loadCalls = testLoader->loadCalls;

			IntrusivePointer<TestResource> resource(resourceManager.load<TestResource>(FilePath(L"lib://test/testpath"), DirectoryPath()));
			Assert::AreEqual(resource->text, AString("test"));
			Assert::AreEqual(getCalls + 1, library.getCalls);
			Assert::AreEqual(loadCalls + 1, testLoader->loadCalls);

			resourceManager.clearCache();
		}
	}

	TEST_METHOD(ResourceManager_loadCached) {
		MemoryGuard guard;
		{
			resourceManager.clearCache();

			TestLibrary& library = (TestLibrary&)resourceManager.Libraries.get(0);
			size_t getCalls = library.getCalls;
			size_t loadCalls = testLoader->loadCalls;

			IntrusivePointer<TestResource> resource(resourceManager.load<TestResource>(FilePath(L"lib://test/testpath"), DirectoryPath()));
			IntrusivePointer<TestResource> resource2(resourceManager.load<TestResource>(FilePath(L"lib://test/testpath"), DirectoryPath()));
			Assert::IsTrue(resource.get() == resource2.get());
			Assert::AreEqual(getCalls + 1, library.getCalls);
			Assert::AreEqual(loadCalls + 1, testLoader->loadCalls);
	
			resourceManager.clearCache();
		}
	}

	TEST_METHOD(ResourceManager_loadFromBuffer) {
		MemoryGuard guard;
		{
			resourceManager.clearCache();

			TestLibrary& library = (TestLibrary&)resourceManager.Libraries.get(0);
			size_t getCalls = library.getCalls;
			size_t loadCalls = testLoader->loadCalls;

			Buffer buffer((const void*)"test", 5);

			IntrusivePointer<TestResource> resource(resourceManager.load<TestResource>(buffer, DirectoryPath()));
			Assert::AreEqual(resource->text, AString("test"));
			Assert::AreEqual(getCalls, library.getCalls);
			Assert::AreEqual(loadCalls + 1, testLoader->loadCalls);

			resourceManager.clearCache();
		}
	}
	};
}

namespace Microsoft::VisualStudio::CppUnitTestFramework {
	template<> static std::wstring ToString<Ghurund::Core::AString>(const Ghurund::Core::AString& t) {
		return convertText<char, wchar_t>(t).Data;
	}
}