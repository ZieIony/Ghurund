#pragma once

#include "core/Color.h"
#include "engine/graphics/material/Material.h"
#include "engine/graphics/material/ValueInput.h"

namespace Ghurund::UI {
    using namespace Ghurund::Engine;
    using namespace ::DirectX;

    class ControlMaterialInputs {
    private:
        Float4Input* backgroundColorInput,* borderColorInput,* cornerRadiusInput;
        FloatInput* borderWidthInput;

    public:
        ControlMaterialInputs(Ghurund::Engine::Material& material) {
			backgroundColorInput = (Float4Input*)material.Inputs.get("backgroundColor");
			//borderColorInput.set((Float4Input*)material.Inputs.get("borderColor"));
            //borderColorInput->addReference();
            //cornerRadiusInput.set((Float4Input*)material.Inputs.get("cornerRadius"));
            //cornerRadiusInput->addReference();
            //borderWidthInput.set((FloatInput*)material.Inputs.get("borderWidth"));
            //borderWidthInput->addReference();
        }

        inline void setBackgroundColor(const Color& color) {
            backgroundColorInput->Value = color.toVector();
        }

        __declspec(property(put = setBackgroundColor)) const Color& BackgroundColor;

        inline void setBorderColor(const Color& color) {
            borderColorInput->Value = color.toVector();
        }

        __declspec(property(put = setBorderColor)) const Color& BorderColor;

        inline void setBorderWidth(float width) {
            borderWidthInput->Value = width;
        }

        __declspec(property(put = setBorderWidth)) float BorderWidth;

        inline void setCornerRadius(const XMFLOAT4& cornerRadius) {
            cornerRadiusInput->Value = cornerRadius;
        }

        __declspec(property(put = setCornerRadius)) const XMFLOAT4& CornerRadius;
    };
}