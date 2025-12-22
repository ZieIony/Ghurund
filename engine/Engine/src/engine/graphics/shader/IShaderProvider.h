#pragma once

#include "IShader.h"

namespace Ghurund::Engine {

    class IShaderProvider:public Noncopyable {
    public:
        virtual IShader* loadBasic() = 0;

        virtual IShader* loadBasicLight() = 0;

        virtual IShader* loadWireframe() = 0;

        virtual IShader* loadOutline() = 0;

        virtual IShader* loadNormals() = 0;

        virtual IShader* loadInvalid() = 0;

        virtual IShader* loadLightPass() = 0;

        virtual IShader* loadBasicSky() = 0;

        virtual IShader* loadAdvancedSky() = 0;
    };
}