#pragma once

#include "engine/graphics/material/Material.h"
#include "engine/parameter/ValueParameter.h"
#include "core/Color.h"

namespace Ghurund::UI {
    using namespace Ghurund::Engine;
    using namespace ::DirectX;

    class ShadowMaterialParameters {
    private:
        IntrusivePointer<Float4Parameter> colorParameter, cornerRadiusParameter;
        IntrusivePointer<Float2Parameter> sizeParameter;
        IntrusivePointer<FloatParameter> elevationParameter;

    public:
        ShadowMaterialParameters(Ghurund::Engine::Material& material) {
            colorParameter.set((Float4Parameter*)material.Parameters.get("color"));
            colorParameter->addReference();
            cornerRadiusParameter.set((Float4Parameter*)material.Parameters.get("cornerRadius"));
            cornerRadiusParameter->addReference();
            sizeParameter.set((Float2Parameter*)material.Parameters.get("size"));
            sizeParameter->addReference();
            elevationParameter.set((FloatParameter*)material.Parameters.get("elevation"));
            elevationParameter->addReference();
        }

        inline void setColor(const Color& color) {
            colorParameter->Value = color.toVector();
        }

        __declspec(property(put = setColor)) const Color& Color;

        inline void setSize(const XMFLOAT2& size) {
            sizeParameter->Value = size;
        }

        __declspec(property(put = setSize)) const XMFLOAT2& Size;

        inline void setElevation(float elevation) {
            elevationParameter->Value = elevation;
        }

        __declspec(property(put = setElevation)) float Elevation;

        inline void setCornerRadius(const XMFLOAT4& cornerRadius) {
            cornerRadiusParameter->Value = cornerRadius;
        }

        __declspec(property(put = setCornerRadius)) const XMFLOAT4& CornerRadius;
    };
}