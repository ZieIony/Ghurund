#pragma once

#include "Material.h"

#include "core/object/Noncopyable.h"
#include "engine/graphics/texture/ITexture.h"

namespace Ghurund::Engine {

	class MaterialProvider:public Noncopyable {
    public:
        virtual Material* makeBasic(ITexture* texture = nullptr) = 0;

        virtual Material* makeBasicLight(ITexture* diffuseTexture = nullptr, ITexture* specularTexture = nullptr, ITexture* normalTexture = nullptr) = 0;

        virtual Material* makeToon(ITexture* texture = nullptr) = 0;

        virtual Material* makeChecker() = 0;

        virtual Material* makeWireframe() = 0;

        virtual Material* makeOutline() = 0;

        virtual Material* makeNormals() = 0;

        virtual Material* makeInvalid() = 0;

        virtual Material* makeLightPass() = 0;

        virtual Material* makeBasicSky() = 0;

        virtual Material* makeAdvancedSky() = 0;
    };
}