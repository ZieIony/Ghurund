#include "TestUtils.h"

namespace UnitTest::Utils {
	template<>
	void runCoroutineBlocking(CoroutineTask<void> coroutine) {
		coroutine.resume();
	}
}
