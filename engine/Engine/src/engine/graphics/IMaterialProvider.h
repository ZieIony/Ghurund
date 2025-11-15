#pragma once

#include "ITexture.h"
#include "IMaterial.h"

namespace Ghurund::Engine {

	class IMaterialProvider:public Noncopyable {
    public:
        virtual IMaterial* makeBasic(ITexture* texture = nullptr) = 0;

        virtual IMaterial* makeBasicLight(ITexture* diffuseTexture = nullptr, ITexture* specularTexture = nullptr, ITexture* normalTexture = nullptr) = 0;

        virtual IMaterial* makeToon(ITexture* texture = nullptr) = 0;

        virtual IMaterial* makeChecker() = 0;

        virtual IMaterial* makeWireframe() = 0;

        virtual IMaterial* makeOutline() = 0;

        virtual IMaterial* makeNormals() = 0;

        virtual IMaterial* makeInvalid() = 0;

        virtual IMaterial* makeLightPass() = 0;

        virtual IMaterial* makeUi() = 0;

        virtual IMaterial* makeText() = 0;

        virtual IMaterial* makeBasicSky() = 0;

        virtual IMaterial* makeAdvancedSky() = 0;
    };
}