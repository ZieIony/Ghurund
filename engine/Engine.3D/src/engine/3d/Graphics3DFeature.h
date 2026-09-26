#pragma once

#include "core/feature/Feature.h"
#include "core/reflection/Type.h"
#include "core/resource/ResourceManager.h"

namespace Ghurund::Engine::_3D {
    using namespace Ghurund::Core;

    class Graphics3DFeature: public Ghurund::Core::Feature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = Graphics3DFeature::GET_TYPE();
#pragma endregion

    protected:
        ResourceManager& resourceManager;

    public:
        inline static const WString MESH_CUBE = L"gh cube mesh";

        inline static const WString MATERIAL_FORWARD_BASIC = L"gh basic forward material";
        inline static const WString MATERIAL_FORWARD_LIT = L"gh lit forward material";
        inline static const WString MATERIAL_FORWARD_NORMALS = L"gh normals forward material";

        Graphics3DFeature(ResourceManager& resourceManager):resourceManager(resourceManager) {}

        virtual ~Graphics3DFeature() = 0 {}
    };
}
