#pragma once

#include "engine/3d/Graphics3DFeature.h"

namespace Ghurund::Engine::_3D::DirectX {
    // this class doesn't do anything yet
    class DxGraphics3DFeature: public Graphics3DFeature {
#pragma region reflection
    protected:
        virtual const Ghurund::Core::Type& getTypeImpl() const override {
            return GET_TYPE();
        }

    public:
        static const Ghurund::Core::Type& GET_TYPE();

        inline static const Ghurund::Core::Type& TYPE = DxGraphics3DFeature::GET_TYPE();
#pragma endregion

    public:
        DxGraphics3DFeature(
            ResourceManager& resourceManager
        ):Graphics3DFeature(resourceManager) {}
    };
}
