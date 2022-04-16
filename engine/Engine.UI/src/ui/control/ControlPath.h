#pragma once

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

            virtual Control* resolve(Control& control) override {
                if (control.Type.extends(ControlContainer::TYPE) && index == 0)
                    return ((ControlContainer&)control).Child;
                if (control.Type.extends(ControlGroup::TYPE)) {
                    ControlGroup& group = (ControlGroup&)control;
                    if (index >= 0 && index < group.Children.Size)
                        return group.Children[index];
                    if (index < 0 && -index <= group.Children.Size)
                        return group.Children[group.Children.Size + index];
                }
                return nullptr;
            }
        };

        Array<std::shared_ptr<StepStrategy>> steps;

    public:
        inline static const AString PARENT_STEP = "Parent";

        static ControlPath parse(const AString& text) {
            List<std::shared_ptr<StepStrategy>> steps;
            AStringView textView = text;
            while (true) {
                if (textView.startsWith(PARENT_STEP)) {
                    steps.add(std::make_shared<ParentStrategy>());
                    textView = textView.substring(PARENT_STEP.Length);
                } else if (textView[0] == '\'') {
                    size_t index = 1;
                    while (true) {
                        if (textView[index] == '\\') {
                            index += 2;
                        } else {
                            index++;
                        }
                        if (index == textView.Length)
                            throw InvalidDataException(std::format("'{}' is not a valid control path (reached EOT, closing '\'' expected)", text).c_str());
                        if (textView[index] == '\'')
                            break;
                    }
                    steps.add(std::make_shared<ChildStrategy>(AString(textView.substring(1, index - 1).Data, index - 1)));
                    textView = textView.substring(index + 1);
                } else if (textView[0] == '{') {
                    size_t index = 1;
                    while (true) {
                        if (textView[index] == '\\') {
                            index += 2;
                        } else {
                            index++;
                        }
                        if (index == textView.Length)
                            throw InvalidDataException(std::format("'{}' is not a valid control path (reached EOT, '}}' expected)", text).c_str());
                        if (textView[index] == '}')
                            break;
                    }
                    /*Type type = Type::byName();
                    steps.add(std::make_shared<TypeStrategy>(type));
                    textView = textView.substring(index);*/
                } else if (textView.begin() != text.begin()) {
                    throw InvalidDataException(std::format("'{}' is not a valid control path (expected '{}' or a control name at position {})", text, PARENT_STEP, textView.Data - text.Data).c_str());
                }
                if (textView[0] == '[') {
                    size_t index = 1;
                    while (true) {
                        if (textView[index] == ']')
                            break;
                        if (index == textView.Length)
                            throw InvalidDataException(std::format("'{}' is not a valid control path (reached EOT, ']' expected)", text).c_str());
                        if(!isdigit(textView[index])&&!(textView[index]=='-'&&index==1))
                            throw InvalidDataException(std::format("'{}' is not a valid control path (invalid index at position)", text, textView.Data - text.Data).c_str());
                        index++;
                    }
                    int childIndex = Ghurund::Core::parse<int>(textView.substring(1, index - 1).Data);
                    steps.add(std::make_shared<IndexStrategy>(childIndex));
                    textView = textView.substring(index + 1);
                } else if (textView.begin() == text.begin()) {
                    throw InvalidDataException(std::format("'{}' is not a valid control path (expected '{}', '{{', '[' or a control name at position 0)", text, PARENT_STEP).c_str());
                }
                if (textView[0] == '.') {
                    textView = textView.substring(1);
                } else if (textView[0] == 0) {
                    return ControlPath(steps);
                } else {
                    throw InvalidDataException(std::format("'{}' is not a valid control path (expected '.' at position {}", text, textView.Data - text.Data).c_str());
                }
            }
        }

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