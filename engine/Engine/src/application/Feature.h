#pragma once

#include "Status.h"
#include "core/Pointer.h"
#include "core/reflection/TypeBuilder.h"

namespace Ghurund {
    using namespace Ghurund::Core;

    class Application;

    class Feature:public Pointer {
#pragma region reflection
    protected:
        static const Ghurund::Core::Type& GET_TYPE();

    public:
        inline static const Ghurund::Core::Type& TYPE = GET_TYPE();
        virtual const Ghurund::Core::Type& getType() const override { return TYPE; }
#pragma endregion

    public:
        virtual ~Feature() {
            uninit();
        }

        virtual void init() = 0;
        virtual void uninit() {}
    };
}