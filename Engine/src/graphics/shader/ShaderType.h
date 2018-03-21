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

        static const ShaderType *values;

    public:
        static const ShaderType VS, PS, GS, HS, DS, CS;

        ShaderType(unsigned int value, const char *text, const char *entryPoint) {
            this->value = value;
            this->text = text;
            this->entryPoint = entryPoint;
        }

        unsigned int getValue() {
            return value;
        }

        operator unsigned int() const { return value; }

        const static ShaderType *getValues();

        static size_t getValueCount() {
            return 6;
        }

        const char *toString() {
            return text;
        }
    };
}