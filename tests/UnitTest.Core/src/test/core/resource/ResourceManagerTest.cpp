#include "utcpch.h"
#include "CppUnitTest.h"
#include "TestLoader.h"
#include "TestResource.h"
#include "TestLibrary.h"
#include "test/utils/MemoryGuard.h"
#include "test/utils/ObjectGuard.h"
#include "test/utils/TestUtils.h"

#include "core/resource/ResourceManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace UnitTest::Utils;
	using namespace Ghurund::Core;

	TEST_CLASS(ResourceManagerTest) {
private:
	Timer timer;
	CoroutineThreadPool threadPool = CoroutineThreadPool(4);
	CoroutineScheduler coroutineScheduler = Ghurund::Core::CoroutineScheduler(threadPool, timer);
	ResourceManager resourceManager = ResourceManager(coroutineScheduler);
	IntrusivePointer<TestLoader> testLoader;

public:
	TEST_METHOD_INITIALIZE(ResourceManagerTest_initialize) {
		testLoader = makeIntrusive<TestLoader>();
		resourceManager.Loaders.set<TestResource>(testLoader.ref());
		resourceManager.Libraries.add(std::make_unique<TestLibrary>());
	}

	TEST_METHOD_CLEANUP(ResourceManagerTest_cleanup) {
		resourceManager.clearCache();
		resourceManager.Loaders.clear();
		resourceManager.Libraries.clear();
		testLoader.set(nullptr);
	}

	TEST_METHOD(ResourceManager_loadFileFromLibrary) {
		MemoryGuard mg;
		ObjectGuard og;
		{
			TestLibrary& library = (TestLibrary&)resourceManager.Libraries.get(0);
			size_t getCalls = library.getCalls;
			size_t loadCalls = testLoader->loadCalls;

			auto path = FilePath(L"lib://test/testpath");
			auto dir = DirectoryPath::getCurrentDirectory();

			IntrusivePointer<TestResource> resource = runCoroutineBlocking(
				resourceManager.load<TestResource>(path, dir, ResourceFormat::AUTO, LoadOption::DONT_CACHE)
			);

			Assert::AreEqual(resource->text, AString("test"));
			Assert::AreEqual(getCalls + 1, library.getCalls);
			Assert::AreEqual(loadCalls + 1, testLoader->loadCalls);
		}
	}

	TEST_METHOD(ResourceManager_loadCached) {
		MemoryGuard mg;
		ObjectGuard og;
		{
			TestLibrary& library = (TestLibrary&)resourceManager.Libraries.get(0);
			size_t getCalls = library.getCalls;
			size_t loadCalls = testLoader->loadCalls;

			auto path = FilePath(L"lib://test/testpath");
			auto dir = DirectoryPath::getCurrentDirectory();

			IntrusivePointer<TestResource> resource = runCoroutineBlocking(resourceManager.load<TestResource>(path, dir));
			IntrusivePointer<TestResource> resource2 = runCoroutineBlocking(resourceManager.load<TestResource>(path, dir));

			Assert::IsTrue(resource.get() == resource2.get());
			Assert::AreEqual(getCalls + 1, library.getCalls);
			Assert::AreEqual(loadCalls + 1, testLoader->loadCalls);

			resourceManager.clearCache();
		}
	}

	TEST_METHOD(ResourceManager_loadFromBuffer) {
		MemoryGuard mg;
		ObjectGuard og;
		{
			TestLibrary& library = (TestLibrary&)resourceManager.Libraries.get(0);
			size_t getCalls = library.getCalls;
			size_t loadCalls = testLoader->loadCalls;

			Buffer buffer((const void*)"test", 5);

			IntrusivePointer<TestResource> resource = runCoroutineBlocking(
				resourceManager.load<TestResource>(buffer, DirectoryPath::getCurrentDirectory(), ResourceFormat::AUTO, LoadOption::DONT_CACHE)
			);

			Assert::AreEqual(resource->text, AString("test"));
			Assert::AreEqual(getCalls, library.getCalls);
			Assert::AreEqual(loadCalls + 1, testLoader->loadCalls);
		}
	}
	};
}
