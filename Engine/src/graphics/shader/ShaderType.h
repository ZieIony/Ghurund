#pragma once

#include "resource/Resource.h"
#include "core/collection/List.h"
#include "ConstantBuffer.h"
#include "Sampler.h"
#include "TextureBufferConstant.h"
#include "TextureConstant.h"

#pragma warning(push, 0)
#include <d3d12.h>
#include <D3Dcompiler.h>
#include "d3dx12.h"
#pragma warning(pop)

#include <wrl.h>

namespace Ghurund {
    using namespace Microsoft::WRL;

    class ShaderType {
    private:
        unsigned int value;
        const char* text;
        const char* entryPoint;
        D3D12_SHADER_VISIBILITY visibility;

        ShaderType(unsigned int value, const char* text, const char* entryPoint, D3D12_SHADER_VISIBILITY visibility) {
            this->value = value;
            this->text = text;
            this->entryPoint = entryPoint;
            this->visibility = visibility;
        }

    public:
        static const ShaderType& VS, & PS, & GS, & HS, & DS, & CS;

        static const ShaderType values[];

        static const ShaderType& fromValue(unsigned int value) {
            if (value == VS.value) {
                return VS;
            } else if (value == PS.value) {
                return PS;
            } else if (value == GS.value) {
                return GS;
            } else if (value == HS.value) {
                return HS;
            } else if (value == DS.value) {
                return DS;
            } else {
                return CS;
            }
        }

        unsigned int getValue() const {
            return value;
        }

        operator unsigned int() const { return value; }

        const char* toString() const {
            return text;
        }

        const char* getEntryPoint() const {
            return entryPoint;
        }

        D3D12_SHADER_VISIBILITY getVisibility() const {
            return visibility;
        }
    };
}