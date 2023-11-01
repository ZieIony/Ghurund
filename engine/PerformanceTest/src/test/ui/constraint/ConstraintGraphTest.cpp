#include "pch.h"
#include "CppUnitTest.h"

#include "ui/constraint/Constraint.h"
#include "ui/constraint/ConstraintGraph.h"
#include "ui/constraint/ValueConstraint.h"
#include "ui/constraint/WrapConstraint.h"
#include "ui/control/ColorView.h"

#include <format>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

using namespace Ghurund::Core;
using namespace Ghurund::UI;

namespace PerformanceTest::UI {
    TEST_CLASS(ConstraintGraphTest) {
public:
    TEST_METHOD(bigGraph) {
        Timer timer;
        List<Constraint*> constraints;
        for (size_t k = 0; k < 100; k++) {
            for (size_t i = 0; i < 20; i++) {
                auto c = ghnew Constraint();
                if (i > 10) {
                    for (size_t j = 1; j <= 3; j++)
                        c->Dependencies.put(constraints[i - j * 3]);
                }
                constraints.add(c);
            }
        }
        ConstraintGraph graph;
        graph.addAll(constraints);
        timer.tick();
        graph.sort();
        timer.tick();
        graph.clear();
        while (!constraints.Empty) {
            Constraint* c = constraints.get(constraints.Size - 1);
            constraints.removeAt(constraints.Size - 1);
            c->release();
        }
        Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(std::format(_T("Sorting time: {}ms."), timer.FrameTimeMs).c_str());
    }
    };
}
