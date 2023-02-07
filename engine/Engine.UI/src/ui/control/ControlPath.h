#pragma once

#include "core/math/Int.h"
#include "core/collection/Array.h"
#include "core/string/String.h"
#include "ui/control/ControlContainer.h"
#include "ui/control/ControlGroup.h"

namespace Ghurund::UI {
    using namespace Ghurund::Core;

    class ControlPath {
    private:
        interface StepStrategy {
            virtual Control* resolve(Control& control) = 0;
        };

        struct ParentStrategy:public StepStrategy {
            virtual Control* resolve(Control& control) override {
                return control.Parent;
            }
        };

        struct ChildStrategy:public StepStrategy {
            AString name;

            ChildStrategy(const AString& name):name(name) {}

            ChildStrategy(const ChildStrategy& other):name(other.name) {}

            ChildStrategy(ChildStrategy&& other)noexcept:name(other.name) {}

            virtual Control* resolve(Control& control) override {
                return control.find(name, false);
            }
        };

        struct IndexStrategy:public StepStrategy {
            int index;

            IndexStrategy(int index):index(index) {}

            IndexStrategy(const IndexStrategy& other):index(other.index) {}

            IndexStrategy(IndexStrategy&& other)noexcept:index(other.index) {}

            virtual Control* resolve(Control& control) override;
        };

        Array<std::shared_ptr<StepStrategy>> steps;

    public:
        inline static const AString PARENT_STEP = "Parent";

        static ControlPath parse(const AString& text);

        ControlPath(const Array<std::shared_ptr<StepStrategy>>& steps):steps(steps) {}

        inline Control* resolve(Control& control) const {
            Control* result = &control;
            for (auto& step : steps) {
                result = step->resolve(*result);
                if (!result)
                    return nullptr;
            }
            return result;
        }
    };
}