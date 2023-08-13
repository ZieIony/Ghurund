#pragma once
#include "core/io/Library.h"
#include "core/resource/ResourcePath.h"

namespace UnitTest {
	using namespace Ghurund::Core;

	class TestLibrary:public Library {
	private:
		std::shared_ptr<Buffer> buffer = std::make_shared<Buffer>("test", 5);

	public:
		mutable size_t getCalls = 0, getResourcePathCalls = 0;

		TestLibrary():Library(L"test") {}

		virtual bool contains(const WString& path) const override {
			return true;
		}

		virtual ResourcePath getResourcePath(const WString& path) const override {
			getResourcePathCalls++;
			return FilePath(L"testpath");
		}

		virtual ResourcePath getResourcePath(const size_t index) const override {
			getResourcePathCalls++;
			return FilePath(L"testpath");
		}

		virtual std::shared_ptr<Buffer> get(const WString& path)  override {
			getCalls++;
			return buffer;
		}

		virtual std::shared_ptr<Buffer> get(const size_t index)  override {
			getCalls++;
			return buffer;
		}

		virtual size_t getSize() const override {
			return 1;
		}
	};
}
