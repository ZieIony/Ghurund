#pragma once

#include "engine/graphics/material/IMaterial.h"
#include "engine/parameter/ValueParameter.h"
#include "core/Color.h"

namespace Ghurund::UI {
    using namespace Ghurund::Engine;
    using namespace ::DirectX;

    class ControlMaterialParameters {
    private:
        IntrusivePointer<Float4Parameter> backgroundColorParameter, borderColorParameter, cornerRadiusParameter;
        IntrusivePointer<Float2Parameter> sizeParameter;
        IntrusivePointer<Float2Parameter> positionParameter;
        IntrusivePointer<FloatParameter> borderWidthParameter;

    public:
        ControlMaterialParameters(Ghurund::Engine::IMaterial& material) {
			backgroundColorParameter.set((Float4Parameter*)material.Parameters.get("backgroundColor"));
			if (backgroundColorParameter != nullptr)
				backgroundColorParameter->addReference();
			//borderColorParameter.set((Float4Parameter*)material.Parameters.get("borderColor"));
            //borderColorParameter->addReference();
            //cornerRadiusParameter.set((Float4Parameter*)material.Parameters.get("cornerRadius"));
            //cornerRadiusParameter->addReference();
            sizeParameter.set((Float2Parameter*)material.Parameters.get("size"));
            sizeParameter->addReference();
            positionParameter.set((Float2Parameter*)material.Parameters.get("position"));
            positionParameter->addReference();
            //borderWidthParameter.set((FloatParameter*)material.Parameters.get("borderWidth"));
            //borderWidthParameter->addReference();
        }

        inline void setBackgroundColor(const Color& color) {
            backgroundColorParameter->Value = color.toVector();
        }

        __declspec(property(put = setBackgroundColor)) const Color& BackgroundColor;

        inline void setBorderColor(const Color& color) {
            borderColorParameter->Value = color.toVector();
        }

        __declspec(property(put = setBorderColor)) const Color& BorderColor;

        inline void setSize(const XMFLOAT2& size) {
            sizeParameter->Value = size;
        }

        __declspec(property(put = setSize)) const XMFLOAT2& Size;

        inline void setPosition(const XMFLOAT2& pos) {
            positionParameter->Value = pos;
        }

        __declspec(property(put = setPosition)) const XMFLOAT2& Position;

        inline void setBorderWidth(float width) {
            borderWidthParameter->Value = width;
        }

        __declspec(property(put = setBorderWidth)) float BorderWidth;

        inline void setCornerRadius(const XMFLOAT4& cornerRadius) {
            cornerRadiusParameter->Value = cornerRadius;
        }

        __declspec(property(put = setCornerRadius)) const XMFLOAT4& CornerRadius;
    };
}