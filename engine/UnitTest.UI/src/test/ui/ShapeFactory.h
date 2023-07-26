#pragma once

#include "core/reflection/Type.h"
#include "ui/loading/ShapeFactory.h"
#include "core/Exceptions.h"

namespace UnitTest {
    class ShapeFactory:public Ghurund::UI::ShapeFactory {
    public:
        virtual std::unique_ptr<Ghurund::UI::Shape> makeShape(const Ghurund::Core::AString& desc) override {
            throw Ghurund::Core::NotImplementedException();
        }
    };
}
