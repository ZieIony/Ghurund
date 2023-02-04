#pragma once

#include "core/reflection/Type.h"
#include "ui/loading/ShapeFactory.h"

namespace UnitTest {
    class ShapeFactory:public Ghurund::UI::ShapeFactory {
    public:
        virtual Ghurund::UI::Shape* makeShape(const Ghurund::Core::AString& desc) override {
            return nullptr;
        }
    };
}
