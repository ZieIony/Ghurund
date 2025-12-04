#pragma once

#include "core/object/Noncopyable.h"
#include "engine/graphics/material/IMaterial.h"
#include "engine/graphics/shader/IShader.h"

namespace Ghurund::Engine {
    using namespace Ghurund::Core;

    class IMaterialFactory:public Noncopyable {
    public:
        virtual IMaterial* makeMaterial(IShader* shader) = 0;
    };
}