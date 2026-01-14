#pragma once

#include "engine/graphics/material/Material.h"
#include "core/Color.h"

namespace Ghurund::UI {
    using namespace Ghurund::Engine;
    using namespace ::DirectX;

    class ShadowMaterialInputs {
    private:
        Float4Input* colorInput,* cornerRadiusInput;
        Float2Input* sizeInput;
        FloatInput* elevationInput;

    public:
        ShadowMaterialInputs(Ghurund::Engine::Material& material) {
			colorInput = (Float4Input*)material.Inputs.get("color");
            cornerRadiusInput = (Float4Input*)material.Inputs.get("cornerRadius");
            sizeInput = (Float2Input*)material.Inputs.get("size");
            elevationInput = (FloatInput*)material.Inputs.get("elevation");
        }

        inline void setColor(const Color& color) {
            colorInput->Value = color.toVector();
        }

        __declspec(property(put = setColor)) const Color& Color;

        inline void setSize(const XMFLOAT2& size) {
            sizeInput->Value = size;
        }

        __declspec(property(put = setSize)) const XMFLOAT2& Size;

        inline void setElevation(float elevation) {
            elevationInput->Value = elevation;
        }

        __declspec(property(put = setElevation)) float Elevation;

        inline void setCornerRadius(const XMFLOAT4& cornerRadius) {
            cornerRadiusInput->Value = cornerRadius;
        }

        __declspec(property(put = setCornerRadius)) const XMFLOAT4& CornerRadius;
    };
}