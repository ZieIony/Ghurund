#pragma once

#include "Shader.h"

namespace Ghurund::Engine {

    class IShaderProvider:public Noncopyable {
    public:
        virtual Shader* loadBasic() = 0;

        virtual Shader* loadBasicLight() = 0;

        virtual Shader* loadWireframe() = 0;

        virtual Shader* loadOutline() = 0;

        virtual Shader* loadNormals() = 0;

        virtual Shader* loadInvalid() = 0;

        virtual Shader* loadLightPass() = 0;

        virtual Shader* loadBasicSky() = 0;

        virtual Shader* loadAdvancedSky() = 0;
    };
}