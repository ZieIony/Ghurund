#pragma once

#include "Ghurund.h"
#include "resource/Resource.h"
#include "collection/List.h"
#include "ConstantBuffer.h"
#include "Sampler.h"
#include "TextureBufferConstant.h"
#include "TextureConstant.h"

#include <d3d12.h>
#include <D3Dcompiler.h>
#include "d3dx12.h"

#include <wrl.h>

using namespace Microsoft::WRL;

namespace Ghurund {
    class ShaderType {
    private:
        unsigned int value;
        const char *text;
        const char *entryPoint;
		D3D12_SHADER_VISIBILITY visibility;

    public:
        static const ShaderType &VS, &PS, &GS, &HS, &DS, &CS;

        ShaderType(unsigned int value, const char *text, const char *entryPoint, D3D12_SHADER_VISIBILITY visibility) {
            this->value = value;
            this->text = text;
            this->entryPoint = entryPoint;
			this->visibility = visibility;
        }

        unsigned int getValue() const {
            return value;
        }

        operator unsigned int() const { return value; }

        const char *toString() const {
            return text;
        }

		const char *getEntryPoint() const {
			return entryPoint;
		}

		D3D12_SHADER_VISIBILITY getVisibility() const {
			return visibility;
		}
    };
}