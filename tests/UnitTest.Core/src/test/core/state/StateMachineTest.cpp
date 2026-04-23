#include "utcpch.h"
#include "CppUnitTest.h"

#include "core/state/StateMachine.h"
#include "test/utils/MemoryGuard.h"
#include "test/utils/TestUtils.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest {
	using namespace UnitTest::Utils;
	using namespace Ghurund::Core;
	using namespace std;

	class TestStateIdle:public MachineState {
	public:
		TestStateIdle():MachineState(_T("idle"), true) {}
	};

	class TestStateInProgress:public MachineState {
	public:
		TestStateInProgress():MachineState(_T("inProgress"), false) {}
	};

	class TestStateSuccess:public MachineState {
	protected:
		TestStateSuccess():MachineState(_T("success"), false) {}
	};

	class TestStateError:public MachineState {
	protected:
		TestStateError():MachineState(_T("error"), true) {}
	};

	TEST_CLASS(StateMachineTest) {
	public:

		TEST_METHOD(StateMachine_required) {
			MemoryGuard guard;
			{
				StateMachine machine;
				machine.putState(ghnew TestStateIdle());
				machine.putState(ghnew TestStateInProgress());
				machine.putTransition(ghnew StateTransition(_T("idle"), _T("inProgress")));
				machine.reset(_T("idle"));
				machine.goToState(_T("inProgress"));
			}
		}
	};
}
