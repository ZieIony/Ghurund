#pragma once

#include "Status.h"
#include "core/Pointer.h"

#include "reflection_0dd3b599_7058_4f3a_935a_3d8d6e68746a.h"

namespace Ghurund {
    class Application;

    class Feature:public Pointer {
        reflection_0dd3b599_7058_4f3a_935a_3d8d6e68746a

    public:
        virtual ~Feature() 	{
            uninit();
        }

        virtual Status init() = 0;
        virtual void uninit() {}
    };
}