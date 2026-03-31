#pragma once
#include "core/io/Library.h"

namespace UnitTest {
	using namespace Ghurund::Core;

	class TestLibrary:public Library {
	private:
		SharedPointer<Buffer> buffer = SharedPointer<Buffer>(ghnew Buffer("test", 5));

	public:
		mutable size_t getCalls = 0, getResourcePathCalls = 0;

		TestLibrary():Library(L"test") {}

		virtual bool contains(const WString& path) const override {
			return true;
		}

		virtual FilePath getAbsolutePath(const WString& path) const override {
			throw NotSupportedException();
		}

		virtual SharedPointer<Buffer> get(const WString& path) const override {
			getCalls++;
			return buffer;
		}

		virtual SharedPointer<Buffer> get(const size_t index) const override {
			getCalls++;
			return buffer;
		}

		virtual size_t getSize() const override {
			return 1;
		}
	};
}
