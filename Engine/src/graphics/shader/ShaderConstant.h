#pragma once

#include "Ghurund.h"

#include <d3d12.h>
#include <dxgi1_4.h>
#include <DirectXMath.h>
#include <D3Dcompiler.h>
#include "d3dx12.h"

#include <wrl.h>

using namespace DirectX;
using namespace Microsoft::WRL;

namespace Ghurund {
    class ShaderConstant {
    protected:
        char *name = nullptr;
        unsigned int bindPoint;
        D3D12_SHADER_VISIBILITY visibility;

    public:
        ShaderConstant(const char *name, unsigned int bindPoint, D3D12_SHADER_VISIBILITY visibility) {
            this->name = copyStrA(name);
            this->bindPoint = bindPoint;
            this->visibility = visibility;
        }

        virtual ~ShaderConstant() {
            delete[] name;
        }

        inline unsigned int getBindPoint() const {
            return bindPoint;
        }

        inline D3D12_SHADER_VISIBILITY getVisibility() const {
            return visibility;
        }
    };
}